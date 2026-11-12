/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef POWER_BLUE_ROBOTICS_POWERSENSEMODULETASK_TASK_HPP
#define POWER_BLUE_ROBOTICS_POWERSENSEMODULETASK_TASK_HPP

#include "power_blue_robotics/PowerSenseModuleTaskBase.hpp"
#include <base/Float.hpp>

namespace power_blue_robotics {

    class PowerSenseModuleTask : public PowerSenseModuleTaskBase {
        friend class PowerSenseModuleTaskBase;

    private:
        size_t m_current_channel = 0;
        size_t m_voltage_channel = 0;

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
    static constexpr double VOLTAGE_GAIN = 11.0;
    static constexpr double CURRENT_OFFSET = 0.33;
    static constexpr double CURRENT_GAIN = 37.8788;
}

#endif
