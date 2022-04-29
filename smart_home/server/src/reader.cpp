#include "reader.hpp"
#include <istream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>

namespace smart_home
{

Reader::Reader()
: m_parser()
{
}

std::ifstream Reader::open(const char* a_fileName)
{
    std::ifstream file;
    file.open(a_fileName, std::ifstream::in);

    return file;
}


std::vector<ConfigData> Reader::read(std::ifstream& a_file, char a_delimeter)
{
	std::string line;
	std::vector<ConfigData> res;

	while(a_file.good())
	{
        getline(a_file, line);
        std::vector<std::string> data = m_parser.extract(line, a_delimeter);

		res.push_back(ConfigData(data[0], data[1], data[2], data[3], data[4], data[5]));
	} 
    return res;
}

} // namespace cpp