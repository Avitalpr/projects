#pragma once

#include <string>
#include <vector>
#include "config_data.hpp"

class Hub_t;
class Config_data;
class AgentHandlePair_t;

namespace smart_home
{

class Loader
{
public:
												
	Loader();
	// void initializeSystem(const std::string& _pathName, Hub_t& _hub);														
	// std::vector<AgentHandlePair_t>& GetAgents();
	// void ExitAgents();
	// void DestroyAgents();
	

bool CreateAgent(const ConfigData& a_confData) const;
															
// private:
	
// 	std::vector<AgentHandlePair_t> m_agents;
	
};	

} // smart_home