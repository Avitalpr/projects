#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace smart_home
{

class Sensor
{
public:
    Sensor() = default;
    virtual ~Sensor() = default;

    Sensor(Sensor const& a_other) = delete;
    Sensor& operator=(Sensor const& a_other) = delete;
    
    virtual void sample() = 0;
    virtual void notify() = 0;
};


} // namespace smart_home
