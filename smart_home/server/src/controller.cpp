#include "controller.hpp"
#include <iostream>
#include "location.hpp"

namespace smart_home
{

TemperatureController::TemperatureController(const ConfigData& a_configData)
: Controller()
, m_data(a_configData)
, m_interests()
{
    m_interests.push_back(Interest(m_data.GetType(), Location(m_data.GetFloor(), m_data.GetRoom())));
}

std::vector<Interest>& TemperatureController::getInterests()
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
    checkTemperature(a_event.data());
}

void TemperatureController::checkTemperature(int a_temperature)
{
    if(a_temperature > 30)
    {
        std::cout << "open air conditioner for cooling\n";
    }
    else if(a_temperature < 15)
    {
        std::cout << "open air conditioner for heating\n";
    }
    else
    {
        std::cout << "temperature is fine\n";
    }
}


} // smart_home
