#include "config_data.hpp"

namespace smart_home
{

ConfigData::ConfigData(std::string const& a_id, std::string const& a_type, std::string const& a_room, std::string const& a_floor, std::string const& a_log, std::string const& a_config)
: m_deviceId(a_id)
, m_type(a_type)
, m_room(a_room)
, m_floor(a_floor)
, m_log(a_log)
, m_config(a_config)
{
}

const std::string& ConfigData::GetDeviceId() const
{
   return m_deviceId;
}

const std::string& ConfigData::GetType() const
{
   return m_type;
}

const std::string& ConfigData::GetRoom() const
{
   return m_room;
}

const std::string& ConfigData::GetFloor() const
{
   return m_floor;
}

const std::string& ConfigData::GetLog() const
{
   return m_log;
}

const std::string& ConfigData::GetConfig() const
{
   return m_config;
}

void ConfigData::SetDeviceId(const std::string& a_deviceId)
{
   m_deviceId = a_deviceId;
}

void ConfigData::SetType(const std::string& a_type)
{
   m_type = a_type;
}

void ConfigData::SetRoom(const std::string& a_room)
{
   m_room = a_room;
}

void ConfigData::SetFloor(const std::string& a_floor)
{
   m_floor = a_floor;
}

void ConfigData::SetLog(const std::string& a_log)
{
   m_log = a_log;
}

void ConfigData::SetConfig(const std::string& a_config)
{
   m_config = a_config;
}

} // namespace smart_home
