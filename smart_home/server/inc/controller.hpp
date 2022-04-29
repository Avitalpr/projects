#pragma once

#include "observer.hpp"
#include "config_data.hpp"
#include "interest.hpp"
#include "event.hpp"
#include <vector>


namespace smart_home
{

class Controller : public Observer
{

public:
    Controller() = default;

    virtual ~Controller() = default;

    virtual bool notify() = 0;
    virtual bool setDevice() = 0;
    virtual bool IsSafety() = 0;
    virtual void initialize(const ConfigData&) = 0;
    virtual void connect() = 0;
    virtual std::vector<Interest>& getInterests() = 0;


private:
    Controller(Controller const&) = delete;
    Controller& operator=(Controller const&) = delete;

private:
    
};


class TemperatureController : public Controller
{
public:
    TemperatureController(const ConfigData& a_configData);//, float a_temp = float());

    bool notify() override;
    bool setDevice() override;
    bool IsSafety() override;

    void initialize(const ConfigData&) override;
    void connect() override;

    std::vector<Interest>& getInterests() override;

    void update(const Event<int>&) override;

private:
    void checkTemperature(int a_temperature);

private:
    
    ConfigData m_data;
    std::vector<Interest> m_interests;

};


} // smart_home