#pragma once

#include "sensor.hpp"
#include "notify.hpp"
#include "event.hpp"

namespace smart_home
{

class TemperatureMeasure
{
public:
    using Type = unsigned char;

    TemperatureMeasure(Type a_type);

    int min() const;
    int max() const;

private:
    void setTemperatureRange(Type a_type);

private:
    Type m_type;
    int m_minTemperature;
    int m_maxTemperature;

};

class TemperatureSensor : public Sensor, Notifier<char>
{

public:
    using Sample = Event<int>;
    using Mode = std::string;

    TemperatureSensor(TemperatureMeasure a_type, Mode const& a_mode);
    
    void sample();
    void notify();

private:
    void generateSample();

private:
    TemperatureMeasure m_type;
    Mode m_mode;
    Sample m_currentSample;
};
    
} // namespace smart_home

