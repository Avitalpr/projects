#pragma once

#include "event.hpp"

namespace smart_home
{


class Observer
{
public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void update(const Event<int>&) = 0;

private:
    Observer(Observer const&) = delete;
    Observer& operator=(Observer const&) = delete;

};

} // smart_home