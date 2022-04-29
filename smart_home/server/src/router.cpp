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
    //m_observers.insert(std::make_pair(a_aspect, std::unordered_set//(std::move(a_observe)));
}

void Router::notify(Interest const& a_aspects, const Event<int>& a_event)
{
    std::cout << "barickkkkkkkk\n";
    auto it = m_observers.find(a_aspects);
    std::cout << "here1\n";
    if(it != m_observers.end())
    {
        std::cout << "here2\n";
        for(auto const& obs: it->second)
        {
            std::cout << "here3\n";
            obs->update(a_event);
        }
        // auto setItr = it->second.find()
        // it->second->update();
    }
}

} // namespace smart_home