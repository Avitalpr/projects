
#pragma once 

#include <string>

namespace smart_home
{

template <typename T>
Event<T>::Event(const DataPayload& a_data, const DateTime& a_timestamp, const Location& a_location, const EventType& a_type)
: m_data(a_data)
, m_timestamp(a_timestamp)
, m_location(a_location)
, m_type(a_type)
{}

template <typename T>
Event<T>::Event(Event&& a_other) noexcept 
: m_data(std::move(a_other.m_data))
, m_timestamp(a_other.m_timestamp)
, m_location(a_other.m_location)
, m_type(std::move(a_other.m_type))
{}

template <typename T>
Event<T>& Event<T>::operator=(Event&& a_other) noexcept 
{
    if(this != &a_other)
    {
        m_data = std::move(a_other.m_data);
        m_timestamp = a_other.m_timestamp;
        m_location = a_other.m_location;
        m_type = std::move(a_other.m_type);
    }

    return *this;
}

template <typename T>
typename Event<T>::DataPayload Event<T>::data() const
{ 
    return m_data; 
}

template <typename T>
DateTime Event<T>::timestamp() const 
{ 
    return m_timestamp;
}

template <typename T>
Location Event<T>::location() const 
{ 
    return m_location; 
}

template <typename T>
typename Event<T>::EventType Event<T>::type() const 
{
    return m_type; 
}

template <typename T>
void Event<T>::data(DataPayload const& a_data)
{
    m_data = a_data;
}

template <typename T>
void Event<T>::timestamp(DateTime const& a_time)
{
    m_timestamp = a_time;
}

template <typename T>
void Event<T>::location(Location const& a_location)
{
    m_location = a_location;
}

template <typename T>
void Event<T>:: type(EventType const& a_type)
{
    m_type = a_type;
}

template <typename T>
std::string Event<T>::toString() const{
    return m_type + " " +m_location.toString() + " " + m_timestamp.toString();// + " " + std::to_string(data);







}

} // namespace smart_home

