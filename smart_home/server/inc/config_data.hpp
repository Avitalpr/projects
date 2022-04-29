#pragma once


#include <string>

namespace smart_home
{

class ConfigData
{
public:
								
	ConfigData(std::string const&, std::string const&, std::string const&, std::string const&, std::string const&, std::string const&);			
							
	const std::string& GetDeviceId() const;
	const std::string& GetLog() const;
	const std::string& GetConfig() const;
	const std::string& GetType() const;
	const std::string& GetFloor() const;
	const std::string& GetRoom() const;
	
	void SetDeviceId(const std::string& _deviceId);
	void SetLog(const std::string& _log);
	void SetConfig(const std::string& _config);
	void SetType(const std::string& _type);
	void SetFloor(const std::string& _floor);
	void SetRoom(const std::string& _room);
			
															
// private:
// 	ConfigData(const ConfigData& _configData) = delete;
// 	const ConfigData& operator = (const ConfigData& _configData) = delete;

private:
	
	std::string	m_deviceId;
	std::string	m_type;	
	std::string	m_room;	
	std::string	m_floor;	
	std::string	m_log;	
	std::string	m_config;					
};

} // namespace smart_home
