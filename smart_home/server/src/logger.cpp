
#include <stdexcept>
#include "logger.hpp"

namespace smart_home
{

size_t Logger::counter = 1;

const char* const Logger::m_logFileName = "./logger/log.txt";

Logger* Logger::pInstance = nullptr;

std::mutex Logger::m_mutex;

Logger& Logger::instance()
{
	static Cleanup cleanup;

	std::lock_guard<std::mutex> guard(m_mutex);
	if (pInstance == nullptr)
		pInstance = new Logger();
	return *pInstance;
}

Logger::Cleanup::~Cleanup()
{
	std::lock_guard<std::mutex> guard(Logger::m_mutex);
	delete Logger::pInstance;
	Logger::pInstance = nullptr;
}

Logger::~Logger()
{
	m_outputStream.close();
}

Logger::Logger()
{
	m_outputStream.open(m_logFileName, std::ios_base::app);
	if (!m_outputStream.good()) {
		throw std::runtime_error("Unable to initialize the Logger!");
	} 
}

void Logger::log(const std::string& inMessage)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	logHelper(inMessage);
}

void Logger::log(const std::vector<std::string>& inMessages)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	for (size_t i = 0; i < inMessages.size(); i++) {
		logHelper(inMessages[i]);
	}
}

void Logger::logHelper(const std::string& inMessage)
{
	m_outputStream << std::to_string(counter++) + ". " << inMessage << std::endl;
}

} // namespace smart_home
