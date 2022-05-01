#pragma once

#include "sensor.hpp"
#include <memory>
#include <vector>

namespace smart_home
{

class SensorManager
{
public:
    using Container = std::vector<std::shared_ptr<Sensor>>;
    explicit SensorManager(Container& a_sensors);

    void run();


private:
    Container& m_systemSensors;

};
    
} // namespace smart_home
