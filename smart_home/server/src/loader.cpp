#include "loader.hpp"
// #include "Hub_t.h"
// #include "AgentApi_t.h"
#include "config_data.hpp"
#include "reader.hpp"
// #include "AgentHandlePair_t.h"
#include <string.h>
#include <dlfcn.h>
#include <iostream>
#include <exception>
#include "controller.hpp"
#include <memory>
#include "router.hpp"

using namespace std;

namespace smart_home
{

Loader::Loader()
{	
}


bool Loader::CreateAgent(const ConfigData& a_confData) const
{
    std::exception ex;
	void* lib_handle;
	Controller* (*fn)(void);
	std::string soPath = "./so/libc" + a_confData.GetType() + ".so";
	
	lib_handle = dlopen(soPath.c_str(), RTLD_LAZY);
	if (!lib_handle)
	{
		std::cout << "beyyyy\n";
		throw ex;
	}

	fn = (Controller*(*)())dlsym(lib_handle, "connect");
	if (dlerror())
	{
		std::cout << "beyyyyeee\n";
		throw ex;
	}	
	std::cout << "beyyygggy\n";
	Controller* agent = fn();
	std::cout << "beyyygggyuuu\n";
	std::cout << agent << '\n';
	agent->connect();//a_hub);
	//agent->initialize(a_confData);
	std::cout << "beyyygggyuuuyyy\n";

    return true;
	
	// AgentHandlePair_t pair(agent, lib_handle);
	
	// return pair;
}


// void Loader:: initializeSystem(const string& _pathName, Hub_t& _hub)
// {
// 	Config_t config(_pathName);
// 	ConfigData_t configData;
	
// 	// create agent and insert pointer to container
// 	while (config.GetConfigData(configData))
// 	{
// 		m_agents.insert(m_agents.end(), CreateAgent(configData, _hub));
// 	}
// }


// void Loader_t:: DestroyAgents()
// {
// 	for (vector<AgentHandlePair_t>::iterator it = m_agents.begin(); it != m_agents.end(); ++it)
// 	{
// 		delete (it->m_agent);	
// 		dlclose(it->m_handle);
// 	}
// }

// void Loader_t:: ExitAgents()
// {
// 	for (vector<AgentHandlePair_t>::iterator it = m_agents.begin(); it != m_agents.end(); ++it)
// 	{
// 		(it->m_agent)->Stop();
// 	}
// }
					
// vector<AgentHandlePair_t>& Loader_t:: GetAgents()
// {
// 	return m_agents;
// }

} // smart_home
