/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "PowerSenseModuleTask.hpp"
#include <power_base/samples/Current.hpp>
#include <power_base/samples/Voltage.hpp>
#include <string>

using namespace power_blue_robotics;

PowerSenseModuleTask::PowerSenseModuleTask(std::string const& name)
    : PowerSenseModuleTaskBase(name)
{
}

PowerSenseModuleTask::~PowerSenseModuleTask()
{
}

bool PowerSenseModuleTask::configureHook()
{
    if (!PowerSenseModuleTaskBase::configureHook())
        return false;

    m_current_index = _current_index.get();
    if (m_current_index < 0) {
        throw std::invalid_argument(
            "current_index must be non-negative, got " + std::to_string(m_current_index));
    }

    m_voltage_index = _voltage_index.get();
    if (m_voltage_index < 0) {
        throw std::invalid_argument(
            "voltage_index must be non-negative, got " + std::to_string(m_voltage_index));
    }

    return true;
}
bool PowerSenseModuleTask::startHook()
{
    if (!PowerSenseModuleTaskBase::startHook())
        return false;
    return true;
}
void PowerSenseModuleTask::updateHook()
{
    PowerSenseModuleTaskBase::updateHook();

    std::vector<raw_io::Analog> analog_samples;
    if (_analog_samples.read(analog_samples) != RTT::NewData) {
        return;
    }

    if (static_cast<int>(analog_samples.size()) <= m_current_index ||
        static_cast<int>(analog_samples.size()) <= m_voltage_index) {
        exception(INVALID_ANALOG_SAMPLES);
        return;
    }

    power_base::samples::Voltage voltage;
    voltage.time = analog_samples[m_voltage_index].time;
    voltage.value = analog_samples[m_voltage_index].data * VOLTAGE_GAIN;
    power_base::samples::Current current;
    current.time = analog_samples[m_current_index].time;
    float current_reading_voltage = analog_samples[m_current_index].data;
    current.value = (current_reading_voltage - CURRENT_OFFSET) * CURRENT_GAIN;

    _voltage.write(voltage);
    _current.write(current);
}
void PowerSenseModuleTask::errorHook()
{
    PowerSenseModuleTaskBase::errorHook();
}
void PowerSenseModuleTask::stopHook()
{
    PowerSenseModuleTaskBase::stopHook();
}
void PowerSenseModuleTask::cleanupHook()
{
    PowerSenseModuleTaskBase::cleanupHook();
}
