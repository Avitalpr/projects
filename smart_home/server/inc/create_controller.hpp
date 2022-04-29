#pragma once

#include "config_data.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <controller.hpp>

namespace smart_home
{

class CreateController
{
public:
    CreateController();

    std::function<std::shared_ptr<Controller>(const ConfigData&)> create(const ConfigData& a_configData);

    std::shared_ptr<Controller> createTemperatureController(const ConfigData& a_configData);


private:
    std::unordered_map<std::string, std::function<std::shared_ptr<Controller>(const ConfigData&)> > m_controllersTable;

};


} // namespace smart home