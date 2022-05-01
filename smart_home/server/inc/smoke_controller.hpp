#pragma once

#include "controller.hpp"
#include "config_data.hpp"
#include "interest.hpp"
#include "event.hpp"
#include <vector>


namespace smart_home
{


class SmokeController : public Controller
{
public:
    SmokeController(const ConfigData& a_configData);

    void initialize(const ConfigData&) override;
    void connect() override;

    std::vector<Interest>& getInterests() override;

    void update(const Event<int>&) override;

private:
    void checkSmoke(bool a_temperature);

private:
    
    ConfigData m_data;
    std::vector<Interest> m_interests;

};


} // smart_home