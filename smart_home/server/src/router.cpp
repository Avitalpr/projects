#include "router.hpp"
#include <iostream>

namespace smart_home
{

Router::Router()
: Subject()
, m_observers()
{
}

void Router::attach(std::shared_ptr<Observer> a_observe, Interest const& a_aspects)
{
    m_observers[a_aspects].insert(a_observe);
}

void Router::notify(Interest const& a_aspects, const Event<int>& a_event)
{
    auto it = m_observers.find(a_aspects);
    if(it != m_observers.end())
    {
        for(auto const& obs: it->second)
        {
            obs->update(a_event);
        }
    }
}

} // namespace smart_home