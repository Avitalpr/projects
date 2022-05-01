#pragma once

#include <memory>
#include "observer.hpp"
#include "subject.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "interest.hpp"
#include "event.hpp"

namespace smart_home
{


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

class Router : public Subject
{
public:
    Router();
    virtual ~Router(){};

    virtual void attach(std::shared_ptr<Observer>, Interest const& a_aspects) override;

// protected:
    virtual void notify(Interest const& a_aspect, const Event<int>& a_event) override;

private:

    std::unordered_map<Interest, std::unordered_set<std::shared_ptr<Observer> >, HashPair > m_observers;

};

} // smart_home