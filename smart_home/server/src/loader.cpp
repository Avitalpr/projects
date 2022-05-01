#include "loader.hpp"
#include "config_data.hpp"
#include "reader.hpp"
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
		throw ex;
	}

	fn = (Controller*(*)())dlsym(lib_handle, "connect");
	if (dlerror())
	{
		throw ex;
	}	

	Controller* agent = fn();

	std::cout << agent << '\n';
	agent->connect();

    return true;
	
}


} // smart_home
