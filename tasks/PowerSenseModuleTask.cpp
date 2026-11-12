/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "PowerSenseModuleTask.hpp"

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

    if (analog_samples.size() <= CURRENT_CHANNEL ||
        analog_samples.size() <= VOLTAGE_CHANNEL) {
        exception(INVALID_ANALOG_SAMPLES);
        return;
    }

    Voltage voltage;
    voltage.time = analog_samples[VOLTAGE_CHANNEL].time;
    voltage.value = analog_samples[VOLTAGE_CHANNEL].data * VOLTAGE_GAIN;
    Current current;
    current.time = analog_samples[CURRENT_CHANNEL].time;
    float current_reading_voltage = analog_samples[CURRENT_CHANNEL].data;
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
