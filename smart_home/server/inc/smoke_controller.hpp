#pragma once

#include "controller.hpp"
#include "config_data.hpp"
#include "interest.hpp"
#include "event.hpp"
#include "device.hpp"
#include <vector>
#include <mutex>


namespace smart_home
{


class SmokeController : public Controller
{
public:
    using Devices = std::vector<std::shared_ptr<Device> >;
    explicit SmokeController(const ConfigData& a_configData, Devices& a_devices);

    void initialize(const ConfigData&) override;
    void connect() override;

    std::vector<Interest> const& getInterests() const override;

    void update(const Event<int>&) override;

private:
    void checkSmoke(bool a_smokeFlag);

private:
    
    ConfigData m_data;
    std::vector<Interest> m_interests;
    mutable std::mutex m_mutex;
    Devices& m_devices;

};


} // smart_home