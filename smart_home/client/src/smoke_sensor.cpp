#include "smoke_sensor.hpp"
#include "protocol.hpp"

namespace smart_home
{

SmokeSensor::SmokeSensor(Mode const& a_mode)
: m_mode(a_mode)
, m_currentSample()
{}


void SmokeSensor::generateSample()
{
    int random = rand() % 100;
    if(random > 50)
    {
        m_currentSample.data(true);
    }
    else{
        m_currentSample.data(false);
    }
}

void SmokeSensor::sample()
{
    generateSample();
    m_currentSample.location(Location("5", "room_55"));
    m_currentSample.timestamp(DateTime());
    m_currentSample.type("smoke alert");  
}
    
void SmokeSensor::notify()
{
    char buffer[256];
    auto size = protocol::pack<bool>(m_currentSample, buffer);
    
    send(buffer, size);
}

} // namespace smart_home


