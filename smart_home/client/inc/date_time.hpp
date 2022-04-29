#pragma once

#include <string> 
#include <cstddef>

namespace smart_home
{

class DateTime
{

public:
    DateTime();
    DateTime(size_t a_hours, size_t a_minutes, size_t a_seconds, size_t a_day, size_t a_month, size_t a_year);
    
    DateTime(const DateTime& a_other) = default;
    DateTime& operator=(const DateTime& a_other) = default;
    
    ~DateTime() = default;

    static DateTime now();

    size_t hours() const;
    size_t minutes() const;
    size_t seconds() const;
    size_t day() const;
    size_t month() const;
    size_t year() const;

    std::string toString() const;
    std::string timeToString() const;
    std::string dateToString() const;

private:
    static const unsigned long YEARS_OFFSET = 1900;

private:
    size_t m_hours;
    size_t m_minutes;
    size_t m_seconds;
    size_t m_day;
    size_t m_month;
    size_t m_year;
};

} // namespace smart_home


#include "./inl/date_time.hxx"