#include "create_controller.hpp"
#include "temperature_controller.hpp"
#include "smoke_controller.hpp"
#include <iostream>
#include <exception>

namespace smart_home
{

CreateController::CreateController(Devices& a_devices)
: m_controllersTable()
, m_devices(a_devices)
{
    m_controllersTable["temperature alert"] = [&](const ConfigData& a_data, Devices& a_devices){
        return createTemperatureController(a_data, m_devices);
    };
    m_controllersTable["smoke alert"] = [&](const ConfigData& a_data, Devices& a_devices){
        return createSmokeController(a_data, m_devices);
    };
}

std::function<std::shared_ptr<Controller>(const ConfigData&, CreateController::Devices&)> CreateController::getController(const ConfigData& a_configData)
{
    std::exception ex;
    auto it = m_controllersTable.find(a_configData.GetType());
    if(it == m_controllersTable.end())
    {
        throw ex;
    }
    return m_controllersTable[a_configData.GetType()];
}

std::shared_ptr<Controller> CreateController::createTemperatureController( const ConfigData& a_configData, Devices& a_devices)
{
    return std::make_shared<TemperatureController>(a_configData, a_devices);
}

std::shared_ptr<Controller> CreateController::createSmokeController( const ConfigData& a_configData, Devices& a_devices)
{
        return std::make_shared<SmokeController>(a_configData, a_devices);
}

} // smart_home