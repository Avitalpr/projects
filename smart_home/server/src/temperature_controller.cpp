#include "temperature_controller.hpp"
#include <iostream>
#include "location.hpp"

namespace smart_home
{

TemperatureController::TemperatureController(const ConfigData& a_configData, Devices& a_devices)
: Controller()
, m_data(a_configData)
, m_interests()
, m_mutex()
, m_devices(a_devices)
{
    m_interests.push_back(Interest(m_data.GetType(), Location(m_data.GetFloor(), m_data.GetRoom())));
}

std::vector<Interest> const& TemperatureController::getInterests() const
{
    return m_interests;
}

void TemperatureController::connect()
{

}

void TemperatureController::initialize(const ConfigData& a_configData)
{

}

void TemperatureController::update(const Event<int>& a_event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    checkTemperature(a_event.data());
}

void TemperatureController::checkTemperature(int a_temperature)
{
    if(a_temperature > 30)
    {
        std::cout << "open air conditioner for cooling\n";
        m_devices[0]->turnOn();
    }
    else if(a_temperature < 15)
    {
        std::cout << "open air conditioner for heating\n";
        m_devices[0]->turnOff();
    }
    else
    {
        std::cout << "temperature is fine\n";
    }
}


} // smart_home
