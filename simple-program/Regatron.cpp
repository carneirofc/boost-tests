#include "Regatron.hpp"
#include "boost/format.hpp"

Regatron::Regatron(){
    this->readDllVersion();
    BOOST_LOG_TRIVIAL(info) << "initializing tcio lib" << std::endl;
    DllInit();
}

Regatron::~Regatron(){
    BOOST_LOG_TRIVIAL(info) << "initializing tcio lib" << std::endl;
    if(DllClose() != DLL_SUCCESS){
      BOOST_LOG_TRIVIAL(fatal) << "failed to close tcio lib" << std::endl;
    }
}


int Regatron::readDllVersion(){
    if (DllReadVersion(&version, &build, dllString) != DLL_SUCCESS){
        throw std::runtime_error("failed to initialize tcio lib.");
    }
    BOOST_LOG_TRIVIAL(info)  << "Version:" << (version >> 16) << "." << (version & 0xff) << " build:" << build << " dllString:" << dllString << std::endl;
};

int Regatron::connect(int port){
   Regatron::connect(port, port);
}

int Regatron::connect(int fromPort, int toPort){
    //search device connected via DIGI RealPort adapter -> /dev/ttyD00 
    if(DllSetSearchDevice2ttyDIGI() != DLL_SUCCESS){
      throw std::runtime_error("failed to set ttyDIGI");
    }
    
    //search device
    usleep((__useconds_t)(1000*1000*2));//hack: while eth and rs232 at the same tc device: wait 2 sec
    BOOST_LOG_TRIVIAL(info) << "searching from " << fromPort << " to " <<toPort << std::endl;
    
    if(DllSearchDevice(fromPort, toPort, &portNrFound) !=  DLL_SUCCESS){
      throw std::runtime_error(str(boost::format("failed to connect to device. Port range (%s, %s)") % fromPort % toPort ));
    }

    //set remote control to RS232
    if(TC4SetRemoteControlInput(2) != DLL_SUCCESS){
      throw  std::runtime_error("failed to set remote control do RS232.");
    }

    //init lib
    if(TC4GetPhysicalValuesIncrement(
      &incDevVoltage, &incDevCurrent, &incDevPower, &incDevResistance,
      &incSysVoltage, &incSysCurrent, &incSysPower, &incSysResistance) != DLL_SUCCESS){
        throw std::runtime_error("failed to get physical values increment.");
    }

    if(TC4GetModuleID(&(this->moduleID)) != DLL_SUCCESS){
      throw std::runtime_error("failed to get module ID.");
    }

    if(Regatron::isMaster()){
      // Get system valus !
      if(TC4GetSystemPhysicalLimitNom(&voltagePhys, &currentPhys, &powerPhys, &resistancePhys) != DLL_SUCCESS){
        throw std::runtime_error("failed to get system physical nominal values.");
      }
    }
}

void Regatron::selectSystem(){
  Regatron::selectModule(SYS_VALUES);
}
void Regatron::selectDevice(){
  Regatron::selectModule(DEV_VALUES);
}

void Regatron::selectModule(int module){
  if(TC4SetModuleSelector(module) != DLL_SUCCESS){
    throw std::runtime_error(str(boost::format("failed to set module selector to %s  (code %s)") % ((module==SYS_VALUES)?"system":"device") % module));
  }
}

void Regatron::readSystem(){
    Regatron::selectSystem();
    if(TC4GetVoltageAct(&sysVoltage) != DLL_SUCCESS){
      throw std::runtime_error("failed to read system voltage");
    }

    if(TC4GetCurrentAct(&sysCurrent) != DLL_SUCCESS){
      throw std::runtime_error("failed to read system current");
    }

    if(TC4GetPowerAct(&sysPower) != DLL_SUCCESS){
      throw std::runtime_error("failed to read system power");
    }
}

void Regatron::moduleIDInfo(){
  if(this->portNrFound == -1){
    BOOST_LOG_TRIVIAL(error) << "not connected." <<std::endl;
  }
  if(this->moduleID == -1){
    BOOST_LOG_TRIVIAL(error) << "module id not defined." <<std::endl;
  }
  if(this->moduleID != 1 && this->portNrFound != -1){
    BOOST_LOG_TRIVIAL(info) << 
      boost::format("module connect at %s is configured as %s, module ID %s.")
        % this->portNrFound % ((this->moduleID==0)?"master":"slave") % this->moduleID << std::endl;
  }
}

bool Regatron::isMaster(){
  return this->moduleID == 0;
}