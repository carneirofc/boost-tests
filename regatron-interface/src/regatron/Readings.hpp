#pragma once
namespace Regatron {
  class Readings{
    private:
    /** One time readings */
      // -- System
      double m_SysVoltagePhysMax;     // [V]
      double m_SysCurrentPhysMax;     // [A]
      double m_SysPowerPhysMax;       // [kW]
      double m_SysResistancePhysMax;  // [mOhm]

      double m_SysVoltagePhysMin;     // [V]
      double m_SysCurrentPhysMin;     // [A]
      double m_SysPowerPhysMin;       // [kW]
      double m_SysResistancePhysMin;  // [mOhm]

      double m_SysVoltagePhysNom;     // [V]
      double m_SysCurrentPhysNom;     // [A]
      double m_SysPowerPhysNom;       // [kW]
      double m_SysResistancePhysNom;  // [mOhm]

      // -- Module 
      double m_ModVoltagePhysMax;     // [V]
      double m_ModCurrentPhysMax;     // [A]
      double m_ModPowerPhysMax;       // [kW]
      double m_ModResistancePhysMax;  // [mOhm]

      double m_ModVoltagePhysMin;     // [V]
      double m_ModCurrentPhysMin;     // [A]
      double m_ModPowerPhysMin;       // [kW]
      double m_ModResistancePhysMin;  // [mOhm]

      double m_ModVoltagePhysNom;     // [V]
      double m_ModCurrentPhysNom;     // [A]
      double m_ModPowerPhysNom;       // [kW]
      double m_ModResistancePhysNom;  // [mOhm]

    /** Monitor readings */
      // System
      struct T_ErrorTree32* m_SysErrorTreeMon;
      struct T_ErrorTree32* m_SysWarningTreeMon;

      // Module
      struct T_ErrorTree32* m_ModErrorTreeMon;
      struct T_ErrorTree32* m_ModWarningTreeMon;

      // -- Regatron Module
      unsigned int m_moduleID = 0;

    public:
        // @todo: Restrict read/write if master ...? Here or upper layer?
        bool isMaster();

        /** One time reading - System @throw std::runtime_exception */
        void readSystemPhys();
        /** One time reading - Module @throw std::runtime_exception */
        void readModulePhys();
        /** One time reading - Module ID*/
        void readModuleID();

        /** Monitor Generic */
        void readGeneric();
        /** Monitor System */
        void readSystem();
        /** Monitor Module */ 
        void readModule();
  };

}