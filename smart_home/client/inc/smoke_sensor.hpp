#pragma once

#include "sensor.hpp"
#include "notify.hpp"
#include "event.hpp"

namespace smart_home
{

class SmokeSensor : public Sensor, Notifier<char>
{

public:
    using Detection = Event<bool>;
    using Mode = std::string;

    SmokeSensor(Mode const& a_mode);
    
    void sample();
    void notify();

private:
    void generateSample();

private:
    Mode m_mode;
    Detection m_currentSample;
};
    
} // namespace smart_home

