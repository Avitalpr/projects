
#include <time.h>

namespace smart_home
{

inline DateTime::DateTime()
{
    *this = now();
}

inline DateTime::DateTime(size_t a_hours, size_t a_minutes, size_t a_seconds, size_t a_day, size_t a_month, size_t a_year)
: m_hours(a_hours)
, m_minutes(a_minutes)
, m_seconds(a_seconds)
, m_day(a_day)
, m_month(a_month)
, m_year(a_year)
{}

inline DateTime DateTime::now()
{
    struct tm* datetime;
    time_t timenow = time(nullptr);
    datetime = localtime(&timenow);

    return DateTime(datetime->tm_hour, datetime->tm_min, datetime->tm_sec, datetime->tm_mday, datetime->tm_mon, datetime->tm_year + YEARS_OFFSET);
}

inline std::string DateTime::toString() const
{
    return timeToString() + "|" + dateToString();
}

inline std::string DateTime::timeToString() const
{
    return std::to_string(m_hours) + ":" + std::to_string(m_minutes) + ":" + std::to_string(m_seconds);
}

inline std::string DateTime::dateToString() const
{
    return std::to_string(m_day) + "." + std::to_string(m_month) + "." + std::to_string(m_year);
}

inline size_t DateTime::hours() const {
    return m_hours; 
}

inline size_t DateTime::minutes() const { 
    return m_minutes;
}

inline size_t DateTime::seconds() const { 
    return m_seconds;
}

inline size_t DateTime::day() const { 
    return m_day; 
}

inline size_t DateTime::month() const { 
    return m_month; 
}

inline size_t DateTime::year() const { 
    return m_year; 
}


} // namespace smart_home

