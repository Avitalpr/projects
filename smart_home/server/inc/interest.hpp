#pragma once

#include <string>
#include "location.hpp"

namespace smart_home
{

class Interest
{
public:
    //using Location = std::string;

    explicit Interest(std::string a_type = std::string(), Location = Location());

    bool equal(Interest const& a_other) const;

    std::string getType() const;
    std::string getLocationRoom() const;
    std::string getLocationFloor() const;



private:
    
    std::string m_type;
    Location m_location;

};

bool operator==(Interest const& a_this, Interest const& a_other);

} // smart_home
