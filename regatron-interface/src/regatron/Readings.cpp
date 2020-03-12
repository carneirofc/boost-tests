#include "Readings.hpp"

#include "log/Logger.hpp"
#include "serialiolib.h"

namespace Regatron {

    void Readings::readModuleID(){
        if(TC4GetModuleID(&(this->m_moduleID)) != DLL_SUCCESS){
          throw std::runtime_error("failed to get module ID.");
        }
    }

    bool Readings::isMaster(){ return (m_moduleID == 0); }

    void Readings::readModulePhys(){

        if(TC4GetModulePhysicalLimitMax(
            &m_ModVoltagePhysMax,
            &m_ModCurrentPhysMax,
            &m_ModPowerPhysMax,
            &m_ModResistancePhysMax
            ) != DLL_SUCCESS){
          throw std::runtime_error("failed to get module physical max limit values.");
        }

        if(TC4GetModulePhysicalLimitMin(
            &m_ModVoltagePhysMin,
            &m_ModCurrentPhysMin,
            &m_ModPowerPhysMin,
            &m_ModResistancePhysMin
            ) != DLL_SUCCESS){
          throw std::runtime_error("failed to get module physical min limit values.");
        }

        if(TC4GetModulePhysicalLimitNom(
            &m_ModVoltagePhysNom,
            &m_ModCurrentPhysNom,
            &m_ModPowerPhysNom,
            &m_ModResistancePhysNom
            ) != DLL_SUCCESS){
          throw std::runtime_error("failed to get module physical nominal values.");
        }
    }

    void Readings::readSystemPhys(){

        if(TC4GetSystemPhysicalLimitMax(
            &m_SysVoltagePhysMax,
            &m_SysCurrentPhysMax,
            &m_SysPowerPhysMax,
            &m_SysResistancePhysMax
            ) != DLL_SUCCESS){
          throw std::runtime_error("failed to get system physical max limit values.");
        }

        if(TC4GetSystemPhysicalLimitMin(
            &m_SysVoltagePhysMin,
            &m_SysCurrentPhysMin,
            &m_SysPowerPhysMin,
            &m_SysResistancePhysMin
            ) != DLL_SUCCESS){
          throw std::runtime_error("failed to get system physical min limit values.");
        }

        if(TC4GetSystemPhysicalLimitNom(
            &m_SysVoltagePhysNom,
            &m_SysCurrentPhysNom,
            &m_SysPowerPhysNom,
            &m_SysResistancePhysNom
            ) != DLL_SUCCESS){
          throw std::runtime_error("failed to get system physical nominal values.");
        }
    }
}