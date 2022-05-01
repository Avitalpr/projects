#include "smoke_controller.hpp"
#include <iostream>
#include "location.hpp"

namespace smart_home
{

SmokeController::SmokeController(const ConfigData& a_configData)
: Controller()
, m_data(a_configData)
, m_interests()
{
    m_interests.push_back(Interest(m_data.GetType(), Location(m_data.GetFloor(), m_data.GetRoom())));
}

std::vector<Interest>& SmokeController::getInterests()
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
    checkSmoke(a_event.data());
}

void SmokeController::checkSmoke(bool a_smokeFlag)
{
    if(a_smokeFlag)
    {
        std::cout << "open sprinkles\n";
    }
    else
    {
        std::cout << "everything is good\n";
    }
}


} // smart_home