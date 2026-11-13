/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef POWER_BLUE_ROBOTICS_POWERSENSEMODULETASK_TASK_HPP
#define POWER_BLUE_ROBOTICS_POWERSENSEMODULETASK_TASK_HPP

#include "power_blue_robotics/PowerSenseModuleTaskBase.hpp"

namespace power_blue_robotics {

    class PowerSenseModuleTask : public PowerSenseModuleTaskBase {
        friend class PowerSenseModuleTaskBase;

    private:
        int m_current_index = -1;
        int m_voltage_index = -1;
        double m_voltage_gain = 11.0; 
        double m_voltage_offset = 0.0;
        double m_current_gain = 37.8788;
        double m_current_offset = 0.33;

    public:
        PowerSenseModuleTask(
            std::string const& name = "power_blue_robotics::PowerSenseModuleTask");
        ~PowerSenseModuleTask();
        bool configureHook();
        bool startHook();
        void updateHook();
        void errorHook();
        void stopHook();
        void cleanupHook();
    };
}

#endif
