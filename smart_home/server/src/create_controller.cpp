#include "create_controller.hpp"
#include <iostream>

namespace smart_home
{

CreateController::CreateController()
: m_controllersTable()
{
    std::cout << "create controller\n";
    m_controllersTable["TestHVAC"] = [&](const ConfigData& a_data){
        return createTemperatureController(a_data);
    };
}

std::function<std::shared_ptr<Controller>(const ConfigData&)> CreateController::create(const ConfigData& a_configData)
{
    std::cout << "create\n";
    std::cout << a_configData.GetType() <<"\n";
    return m_controllersTable[a_configData.GetType()];
}

std::shared_ptr<Controller> CreateController::createTemperatureController( const ConfigData& a_configData)
{
    std::cout << "create temperature\n";
    return std::make_shared<TemperatureController>(a_configData);
}

} // smart_home