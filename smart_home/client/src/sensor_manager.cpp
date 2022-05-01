#include "sensor_manager.hpp"
#include "temperature_sensor.hpp"
#include "smoke_sensor.hpp"

namespace smart_home
{
    
SensorManager::SensorManager(SensorManager::Container& a_sensors)
: m_systemSensors(a_sensors)
{}

void SensorManager::run()
{
    for(auto& elem : m_systemSensors)
    {
        elem->sample();
        elem->notify();
    }
}

} // namespace smart_home

