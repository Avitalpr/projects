#include "create_controller.hpp"
#include "smoke_controller.hpp"
#include <iostream>
#include <exception>

namespace smart_home
{

CreateController::CreateController()
: m_controllersTable()
{
    m_controllersTable["temperature alert"] = [&](const ConfigData& a_data){
        return createTemperatureController(a_data);
    };
    m_controllersTable["smoke alert"] = [&](const ConfigData& a_data){
        return createSmokeController(a_data);
    };
}

std::function<std::shared_ptr<Controller>(const ConfigData&)> CreateController::getController(const ConfigData& a_configData)
{
    std::exception ex;
    auto it = m_controllersTable.find(a_configData.GetType());
    if(it == m_controllersTable.end())
    {
        throw ex;
    }
    return m_controllersTable[a_configData.GetType()];
}

std::shared_ptr<Controller> CreateController::createTemperatureController( const ConfigData& a_configData)
{
    return std::make_shared<TemperatureController>(a_configData);
}

std::shared_ptr<Controller> CreateController::createSmokeController( const ConfigData& a_configData)
{
        return std::make_shared<SmokeController>(a_configData);
}

} // smart_home