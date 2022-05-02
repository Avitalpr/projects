#pragma once

#include "observer.hpp"
#include "config_data.hpp"
#include "interest.hpp"
#include <vector>


namespace smart_home
{


class Controller : public Observer
{

public:
    Controller() = default;

    virtual ~Controller() = default;

    virtual void initialize(const ConfigData&) = 0;
    virtual void connect() = 0;
    virtual std::vector<Interest> const& getInterests() const = 0;


private:
    Controller(Controller const&) = delete;
    Controller& operator=(Controller const&) = delete;
    
};


} // smart_home
