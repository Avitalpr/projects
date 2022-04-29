#include "temperature_sensor.hpp"
#include "protocol.hpp"

namespace smart_home
{

void TemperatureMeasure::setTemperatureRange(Type a_type)
{
    if(m_type == 'C')
    {
        m_minTemperature = -40;
        m_maxTemperature = 100;
    }
    else if(m_type == 'F')
    {
        m_minTemperature = -40;
        m_maxTemperature = 212;
    }
}

TemperatureMeasure::TemperatureMeasure(Type a_type)
: m_type(a_type)
{
    setTemperatureRange(m_type);
}

int TemperatureMeasure::min() const
{
    return m_minTemperature;
}

int TemperatureMeasure::max() const
{
    return m_maxTemperature;
}

TemperatureSensor::TemperatureSensor(TemperatureMeasure a_type, Mode const& a_mode)
: m_type(a_type)
, m_mode(a_mode)
, m_currentSample()
{}

void TemperatureSensor::sample()
{
    // random float temperatures generator
    
    //float temperature = m_type.min() + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(m_type.max() - m_type.min())));
    int temperature = 45;
    DateTime timestamp;
    Location location("1", "22");
    
    m_currentSample.data(temperature);
    m_currentSample.location(location);
    m_currentSample.timestamp(timestamp);
    m_currentSample.type("temperature alert");
    
}
    
void TemperatureSensor::notify()
{
    char buffer[256];
    auto size = protocol::pack<int>(m_currentSample, buffer);
    
    send(buffer, size);

}

} // namespace smart_home


