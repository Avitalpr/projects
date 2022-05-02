#pragma once

#include <memory>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "observer.hpp"
#include "subject.hpp"
#include "interest.hpp"
#include "event.hpp"
#include "utils.hpp"


namespace smart_home
{


class Router : public Subject
{
public:
    Router();
    virtual ~Router() = default;

    virtual void attach(std::shared_ptr<Observer>, Interest const& a_aspects) override;
    virtual void notify(Interest const& a_aspect, const Event<int>& a_event) override;

private:

    std::unordered_map<Interest, std::unordered_set<std::shared_ptr<Observer> >, HashPair > m_observers;
    std::vector<Args> m_observersToUpdate;
    mutable std::mutex m_mutex;
};

} // smart_home