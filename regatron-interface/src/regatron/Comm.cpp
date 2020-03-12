#include "Comm.hpp"

#include <iostream>
#include "serialiolib.h"

#include "fmt/format.h"
#include "log/Logger.hpp"

namespace Regatron {
  Comm::Comm(int port):
          m_port(port), m_version(std::make_shared<Regatron::Version>()), m_readings(std::make_shared<Regatron::Readings>()) {
      this->m_version->readDllVersion();
      LOG_INFO("initializing tcio lib");
      DllInit();
  }

  Comm::Comm(){
    Comm(1);
  }

  Comm::~Comm(){
      if(DllClose() != DLL_SUCCESS){
        LOG_ERROR("failed to close tcio lib");
      }
      LOG_INFO("regatron obj deleted");
  }

  void Comm::connect(){
    this->connect(m_port, m_port);
  }

  void Comm::connect(int port){
    this->connect(port, port);
  }

  void Comm::connect(int fromPort, int toPort){
      //search device connected via DIGI RealPort adapter -> /dev/ttyD00
      if(DllSetSearchDevice2ttyDIGI() != DLL_SUCCESS){
        throw std::runtime_error("failed to set ttyDIGI");
      }

      //search device
      usleep((__useconds_t)(1000*1000*2));//hack: while eth and rs232 at the same tc device: wait 2 sec
      LOG_INFO("searching from {} to {}", fromPort , toPort);

      if(DllSearchDevice(fromPort, toPort, &m_portNrFound) !=  DLL_SUCCESS){
        throw std::runtime_error(fmt::format("failed to connect to device. Port range ({}, {})", fromPort, toPort ));
      }

      //set remote control to RS232
      if(TC4SetRemoteControlInput(2) != DLL_SUCCESS){
        throw std::runtime_error("failed to set remote control do RS232.");
      }

      //init lib
      if(TC4GetPhysicalValuesIncrement(
        &incDevVoltage, &incDevCurrent, &incDevPower, &incDevResistance,
        &incSysVoltage, &incSysCurrent, &incSysPower, &incSysResistance) != DLL_SUCCESS){
          throw std::runtime_error("failed to get physical values increment.");
      }

      if(TC4GetModuleID(&(this->m_moduleID)) != DLL_SUCCESS){
        throw std::runtime_error("failed to get module ID.");
      }

      // One time readings... update on every new connection
      if(this->isMaster()){m_readings->readSystemPhys();}
      m_readings->readModulePhys();
  }

  void Comm::selectSystem(){
    this->selectModule(SYS_VALUES);
  }
  void Comm::selectDevice(){
    this->selectModule(DEV_VALUES);
  }

  void Comm::selectModule(int module){
    if(TC4SetModuleSelector(module) != DLL_SUCCESS){
      throw std::runtime_error(fmt::format("failed to set module selector to {} (code {})", ((module==SYS_VALUES)?"system":"device"), module));
    }
  }

  void Comm::readSystem(){
      this->selectSystem();
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

  void Comm::readDevice(){
      this->selectDevice();
      if(TC4GetVoltageAct(&devVoltage) != DLL_SUCCESS){
        throw std::runtime_error("failed to read device voltage");
      }

      if(TC4GetCurrentAct(&devCurrent) != DLL_SUCCESS){
        throw std::runtime_error("failed to read device current");
      }

      if(TC4GetPowerAct(&devPower) != DLL_SUCCESS){
        throw std::runtime_error("failed to read device power");
      }
  }

  void Comm::moduleIDInfo(){
    if(this->m_portNrFound == -1){
      LOG_WARN("not connected to any device.");
    }
    if(this->m_portNrFound != -1){
      LOG_INFO(fmt::format("module connect at {} is configured as {}, module ID {}.",
          this->m_portNrFound, ((this->m_moduleID==0)?"master":"slave"), this->m_moduleID));
    }
  }

  bool Comm::isMaster(){
    return this->m_moduleID == 0;
  }
}
