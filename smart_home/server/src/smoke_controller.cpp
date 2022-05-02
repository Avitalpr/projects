#include "smoke_controller.hpp"
#include <iostream>
#include "location.hpp"

namespace smart_home
{

SmokeController::SmokeController(const ConfigData& a_configData, Devices& a_devices)
: Controller()
, m_data(a_configData)
, m_interests()
, m_mutex()
, m_devices(a_devices)
{
    m_interests.push_back(Interest(m_data.GetType(), Location(m_data.GetFloor(), m_data.GetRoom())));
}

std::vector<Interest> const& SmokeController::getInterests() const
{
    return m_interests;
}

void SmokeController::connect()
{

}

void SmokeController::initialize(const ConfigData& a_configData)
{

}

void SmokeController::update(const Event<int>& a_event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    checkSmoke(a_event.data());
}

void SmokeController::checkSmoke(bool a_smokeFlag)
{
    if(a_smokeFlag)
    {
        std::cout << "open sprinkles\n";
        m_devices[1]->turnOn();
    }
    else
    {
        std::cout << "everything is good\n";
        m_devices[1]->turnOff();
    }
}


} // smart_home