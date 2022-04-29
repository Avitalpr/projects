#pragma once

#include <memory>
#include "observer.hpp"
#include "interest.hpp"
#include "event.hpp"

namespace smart_home
{

class Subject
{
public:
    Subject() = default;
    virtual ~Subject() = default;

    virtual void attach(std::shared_ptr<Observer>, Interest const&) = 0;

// protected:
    virtual void notify(Interest const&, const Event<int>& a_event) = 0;

private:
    Subject(Subject const&) = delete;
    Subject& operator=(Subject const&) = delete;

};

} // smart_home