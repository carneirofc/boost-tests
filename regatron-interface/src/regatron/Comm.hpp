
#pragma once

#define SYS_VALUES 64
#define DEV_VALUES 0

#include <memory>
#include <unistd.h>

namespace Regatron {

  class Limits {
    public:
      double voltagePhysMax;     // [V]
      double currentPhysMax;     // [A]
      double powerPhysMax;       // [kW]
      double resistancePhysMax; // [mOhm]

      double voltagePhysMin;     // [V]
      double currentPhysMin;     // [A]
      double powerPhysMin;       // [kW]
      double resistancePhysMin; // [mOhm]
  };

  class Version {
    public:
      /** One time readings */
      // -- Dll Version
      unsigned int versionDllMajorMinor; // (xx.68.00) and (03.xx.00)
      unsigned int versionDllBuild;      // (03.68.xx)
      char versionDllString[128];
      // -- DSP Firwmare
      unsigned int versionDSPMain;
      unsigned int versionDSPSub;
      unsigned int versionDSPRevision;
      // -- DSP software
      unsigned int versionPeripherieDSP;
      unsigned int versionPeripherieAuxiliaryDSP; //  (e.g. 10, read as 0.10)
      unsigned int versionModulatorAuxiliaryDSP;  //  (e.g. 23, read as 0.24)
      unsigned int versionBootloader;             //  (e.g. 04, read as 0.04)
  };

  class IBC {
    public:
      // -- IBC Board related
      double IBCInvTemp = 0;
      double IBCTransformerSecCurrent = 0;
      unsigned short IBCState = 0;
      unsigned short IBCFirmwareVer = 0;
  };

  class Comm {
    private:
      int port = 0;
      int portNrFound = -1;

      // Software version
      std::shared_ptr<Regatron::Version> version;

      // Limits
      std::shared_ptr<Regatron::Limits> sysLimits;
      std::shared_ptr<Regatron::Limits> devLimits;

      // IBC
      std::shared_ptr<Regatron::IBC> ibc;

      // -- Regatron Module
      unsigned int moduleID = 0;

      // Increment (internal usage)
      double incDevVoltage = 0.0;
      double incDevCurrent = 0.0;
      double incDevPower = 0.0;
      double incDevResistance = 0.0;
      double incSysVoltage = 0.0;
      double incSysCurrent = 0.0;
      double incSysPower = 0.0;
      double incSysResistance = 0.0;


      // Nominal values
      double voltagePhys = 0.0;
      double currentPhys = 0.0;
      double powerPhys = 0.0;
      double resistancePhys = 0.0;

      /** Monitor readings */
      struct T_ErrorTree32* sysErrorTreeMon;
      struct T_ErrorTree32* sysWarningTreeMon;

      struct T_ErrorTree32* devErrorTreeMon;
      struct T_ErrorTree32* devWarningTreeMon;

      // System actual values
      double sysVoltage = 0.0;
      double sysCurrent = 0.0;
      double sysPower = 0.0;
      unsigned int sysState = 0;

      // Device actual valuse
      double devVoltage = 0.0;
      double devCurrent = 0.0;
      double devPower = 0.0;
      unsigned int devState = 0;

      void readDllVersion();
      void readDSPVersion();
      void selectModule(int);
      void selectDevice();
      void selectSystem();

    public:
      Comm(int);
      Comm();
      ~Comm();
      void connect();
      void connect(int);
      void connect(int, int);
      bool isMaster();
      void moduleIDInfo();
      void readSystem();
      void readDevice();
      void readTemps();
  };

#define IBC_STATE_INVALID  0x0001
#define IBC_STATE_POWER_UP 0x0004
#define IBC_SATE_READY     0x0010
#define IBC_STATE_RUNNING  0x010
#define IBC_STATE_WARNING  0x0400
#define IBC_STATE_ERROR    0x1000
#define IBC_STATE_STOPPED  0x4000
#define IBC_STATE_UPDATE   0x8000

#define REG_STATE_POWER_UP 2
#define REG_STATE_READY    4
#define REG_STATE_RUN      8
#define REG_STATE_WARNING  10
#define REG_STATE_ERROR    12
#define REG_STATE_STOP     14

}