#pragma once

#include <memory>
#include <vector>
#include <string>

#include "observer.hpp"
#include "event.hpp"
#include "interest.hpp"


namespace smart_home
{

class Args
{
public:
Args(std::shared_ptr<Observer> const& a_observer, const Event<int>& a_event)
: m_observer(a_observer)
, m_event(a_event)
{
}

std::shared_ptr<Observer> const& m_observer;
const Event<int>& m_event;

};

struct HashPair {
    size_t operator()(const Interest& p) const
    {
        size_t res = 0;
        auto hash1 = std::hash<std::string>{}(p.getType());
        auto hash2 = std::hash<std::string>{}(p.getLocationRoom());
        auto hash3 = std::hash<std::string>{}(p.getLocationFloor());
 
        if(hash1 != hash2 || hash1 != hash3)
        {
            res ^= hash1 + 0x9e3779b9 + (res << 6) + (res >> 2);
            res ^= hash2 + 0x9e3779b9 + (res << 6) + (res >> 2);
            res ^= hash3 + 0x9e3779b9 + (res << 6) + (res >> 2);
            return hash1 ^ hash2 ^ hash3;             
        }
         
        return res;
    }
};

} // namespace smart_home
