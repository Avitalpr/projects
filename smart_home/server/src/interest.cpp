#include "interest.hpp"
#include <iostream>

namespace smart_home
{

Interest::Interest(std::string a_type, Location a_location)
: m_type(a_type)
, m_location(a_location)
{
}


bool Interest::equal(Interest const& a_other) const
{
    if(m_type == a_other.m_type && m_location == a_other.m_location)
    {
        return true;
    }
    return false;
}

std::string Interest::getType() const
{
    return m_type;
}

std::string Interest::getLocationRoom() const
{
    return m_location.room();
}

std::string Interest::getLocationFloor() const
{
    return m_location.floor();
}

bool operator==(Interest const& a_this, Interest const& a_other)
{
    return a_this.equal(a_other);
}


} // namespace smart_home