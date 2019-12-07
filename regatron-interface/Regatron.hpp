
#pragma once

#include <iostream>
#include <unistd.h>
#include "serialiolib.h"
#include "boost/log/trivial.hpp"

#define SYS_VALUES 64
#define DEV_VALUES 0

class RegatronException : public std::runtime_error{

};

class Regatron{
private:
  int portNrFound = -1;
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

  double sysVoltage;
  double sysCurrent;
  double sysPower;

  void readDllVersion();

  void selectModule(int);
  void selectDevice();
  void selectSystem();

public:
  Regatron();
  ~Regatron();
  void connect(int);
  void connect(int, int);
  bool isMaster();
  void moduleIDInfo();
  void readSystem();
};