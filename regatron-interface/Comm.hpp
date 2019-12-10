
#pragma once

#define SYS_VALUES 64
#define DEV_VALUES 0

namespace Regatron {

  class Comm{
  private:
    int portNrFound = -1;
    unsigned int version; //major and minor
    unsigned int build;
    unsigned int moduleID = 0;
    char dllString[128];

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

    // System actual valuse
    double sysVoltage = 0.0;
    double sysCurrent = 0.0;
    double sysPower = 0.0;
    unsigned int sysState = 0;

    // Device actual valuse
    double devVoltage = 0.0;
    double devCurrent = 0.0;
    double devPower = 0.0;
    unsigned int devState = 0;

    // IBC
    double IBCInvTemp = 0;
    double IBCTransformerSecCurrent = 0;
    unsigned short IBCState = 0;
    unsigned short IBCFirmwareVer = 0;

    void readDllVersion();
    void selectModule(int);
    void selectDevice();
    void selectSystem();

  public:
    Comm();
    ~Comm();
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