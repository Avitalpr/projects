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
    std::cout << "hereeeee\n";
    if(m_type == a_other.m_type && m_location == a_other.m_location)
    {
        std::cout << "hereeeeein\n";
        return true;
    }
    std::cout << "hereeeeeout\n";
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
    std::cout << a_this.getType() << " " << a_other.getType() << std::endl;
    std::cout << a_this.getLocationRoom() << " " << a_other.getLocationRoom() << std::endl;
    std::cout << a_this.getLocationFloor() << " " << a_other.getLocationFloor() << std::endl;
    return a_this.equal(a_other);
    // return a_this == a_other;
    // return true;
}


} // namespace smart_home