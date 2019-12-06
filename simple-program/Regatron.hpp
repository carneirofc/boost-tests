
#pragma once

#include <iostream>
#include <unistd.h>
#include "serialiolib.h"
#include "boost/log/trivial.hpp"

#define SYS_VALUES 64
#define DEV_VALUES 0

class Regatron{
private:
  int result = 0;
  int portNrFound = -1;
  unsigned int connectionType = 0;
  unsigned int version; //major and minor
  unsigned int build;
  unsigned int moduleID = -1;
  char dllString[128];

  double incDevVoltage = 0.0;
  double incDevCurrent = 0.0;
  double incDevPower = 0.0;
  double incDevResistance = 0.0;
  double incSysVoltage = 0.0;
  double incSysCurrent = 0.0;
  double incSysPower = 0.0;
  double incSysResistance = 0.0;
  double voltagePhys;
  double currentPhys;
  double powerPhys;
  double resistancePhys;
  double voltage;
  double current;
  double power;
  double resitance;
  double randFactor;
  double randValue;

  double sysVoltage;
  double sysCurrent;
  double sysPower;

  int readDllVersion();

  void selectModule(int);
  void selectDevice();
  void selectSystem();

public:
  Regatron();
  ~Regatron();
  int connect(int);
  int connect(int, int);
  bool isMaster();
  void moduleIDInfo();
  void readSystem();
};