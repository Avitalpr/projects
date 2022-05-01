#ifndef EVENT_HPP
#define EVENT_HPP


#include <string> 
#include "date_time.hpp"
#include "location.hpp"

namespace smart_home
{

template <typename T>
class Event
{

public:
    using EventType = std::string;
    using DataPayload = T;

    Event() = default;
    Event(const DataPayload& a_data, const DateTime& a_timestamp, const Location& a_location, const EventType& a_type);
    
    Event(const Event& a_other) = default;

    Event(Event&& a_other) noexcept;
    
    Event& operator=(const Event& a_other) = default;
    Event& operator=(Event&& a_other) noexcept;
    ~Event() = default;

    DataPayload data() const;
    DateTime timestamp() const;
    Location location() const;
    EventType type() const;

    void data(DataPayload const& a_data);
    void timestamp(DateTime const& a_time);
    void location(Location const& a_location);
    void type(EventType const& a_type);

    std::string toString() const;

private:
    DataPayload m_data;
    DateTime m_timestamp;
    Location m_location;
    EventType m_type;
};

} // namespace smart_home


#endif // EVENT_HPP

#include "./inl/event.hxx"