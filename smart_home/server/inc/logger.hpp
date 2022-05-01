
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>

namespace smart_home
{
	
class Logger
{

public:
    static size_t counter;
	static Logger& instance();

	void log(const std::string& inMessage);
	void log(const std::vector<std::string>& inMessages);

protected:
	static Logger* pInstance;
	static const char* const m_logFileName;
	std::ofstream m_outputStream;

	friend class Cleanup;
	class Cleanup
	{
	public:
		~Cleanup();
	};

	void logHelper(const std::string& inMessage);

private:
	Logger();
	virtual ~Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	static std::mutex m_mutex;
};

} // namespace smart_home
