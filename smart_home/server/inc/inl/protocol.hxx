#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "event.hpp"


namespace protocol
{
    
inline void insertToBuffer(std::string a_str, char* a_buffer, size_t& a_offset)
{
    a_buffer[a_offset] = a_str.size();
    strcpy(a_buffer + (a_offset + 1), a_str.c_str());
    a_offset += (a_str.size() + 1);
}


template <typename T>
size_t pack(smart_home::Event<T> const& a_event, char* a_buffer)
{
    size_t offset = 1;

    insertToBuffer(a_event.type(), a_buffer, offset);
    insertToBuffer(a_event.location().toString(), a_buffer, offset);
    insertToBuffer(std::to_string(a_event.data()), a_buffer, offset);
    insertToBuffer(a_event.timestamp().toString(), a_buffer, offset);
    
    a_buffer[0] = offset;
    return offset;

}

inline smart_home::DateTime createTimeStamp(std::string& a_time)
{
    auto pos1 = a_time.find((':'));
    auto hours = a_time.substr(0, pos1);
    auto pos2 = a_time.find(':', pos1 + 1);
    auto minutes = a_time.substr(pos1 + 1, pos2 - pos1 - 1);
    auto pos3 = a_time.find('|', pos2 + 1);
    auto seconds = a_time.substr(pos2 + 1, pos3 - pos2 - 1);

    auto pos4 = a_time.find('.', pos3 + 1);
    auto day = a_time.substr(pos3 + 1, pos4 - pos3 - 1);
    auto pos5 = a_time.find('.', pos4 + 1);
    auto month = a_time.substr(pos4 + 1, pos5 - pos4 - 1);
    auto year = a_time.substr(pos5 + 1);

    return smart_home::DateTime(std::stoul(hours, 0, 0), std::stoul(minutes, 0, 0), std::stoul(seconds, 0, 0), std::stoul(day, 0, 0), std::stoul(month,0,0), std::stoul(year,0,0));
}

inline smart_home::Location createLocation(std::string& a_location)
{
    auto pos = a_location.find(('^'));
    auto floor = a_location.substr(0, pos);
    auto room = a_location.substr(pos + 1);

    return smart_home::Location(floor, room);
}


template <typename T>
smart_home::Event<T> unpack(char const* a_message)
{
    std::vector<std::string> vec;
    vec.reserve(4);
    for(size_t i = 2; i < size_t(a_message[0]); i += (a_message[i - 1] + 1))
    {
        std::string str(a_message + i, a_message + (i + a_message[i - 1]));
        vec.push_back(str);
    }

    return smart_home::Event<T>(std::stoul(vec[2], 0, 0), createTimeStamp(vec[3]), createLocation(vec[1]),  vec[0]);
}

} // namespace protocol


