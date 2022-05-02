#include "router.hpp"
#include <iostream>
#include "thread.hpp"
#include <algorithm>

namespace smart_home
{

Router::Router()
: Subject()
, m_observers()
, m_observersToUpdate()
, m_mutex()
{
}



static void* innerUpdate(void* a_context)
{
    smart_home::Args* args = static_cast<smart_home::Args*>(a_context);

    args->m_observer->update(args->m_event);
    return nullptr;
}

void Router::attach(std::shared_ptr<Observer> a_observe, Interest const& a_aspects)
{
    m_observers[a_aspects].insert(a_observe);
}

void Router::notify(Interest const& a_aspects, const Event<int>& a_event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    auto it = m_observers.find(a_aspects);
    if(it != m_observers.end())
    {
        for(auto const& obs: it->second)
        {
            // m_observersToUpdate.push_back(Args(obs, a_event));
            m_observersToUpdate.push_back(std::move(Args(obs, a_event)));
        }
    }
    if(!m_observersToUpdate.empty())
    {
        mt::ThreadGroup<Args> group(m_observersToUpdate, innerUpdate);
        group.join();
        m_observersToUpdate.clear();
    }

}

} // namespace smart_home