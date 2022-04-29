#pragma once

#include <cstdint>

namespace smart_home
{

class Location
{

public:
    using FloorNumber = std::string;
    using RoomNumber = std::string;

    Location() = default;
    Location(FloorNumber a_floor, RoomNumber a_room);
    
    Location(const Location& a_other) = default;
    Location& operator=(const Location& a_other) = default;
    ~Location() = default;

    FloorNumber floor() const;
    RoomNumber room() const;

    std::string toString() const;

    bool equal(Location const& a_other) const;

private:
    FloorNumber m_floor;
    RoomNumber m_room;
};



bool operator==(Location const& a_lop, Location const& a_rop);

} // namespace smart_home

#include "./inl/location.hxx"
