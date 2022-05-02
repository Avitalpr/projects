#pragma once

#include "config_data.hpp"
#include "device.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include "controller.hpp"

namespace smart_home
{


class CreateController
{
public:
    using Devices = std::vector<std::shared_ptr<Device> >;
    explicit CreateController(Devices& a_devices);

    std::function<std::shared_ptr<Controller>(const ConfigData&, Devices&)> getController(const ConfigData& a_configData);

    std::shared_ptr<Controller> createTemperatureController(const ConfigData& a_configData, Devices& a_devices);
    std::shared_ptr<Controller> createSmokeController(const ConfigData& a_configData, Devices& a_devices);


private:
    std::unordered_map<std::string, std::function<std::shared_ptr<Controller>(const ConfigData&, Devices&)> > m_controllersTable;
    Devices& m_devices;
};


} // namespace smart home