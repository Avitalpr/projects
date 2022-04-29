#pragma once

#include <fstream>
#include <unordered_map>
#include "parser.hpp"
#include "config_data.hpp"

namespace smart_home
{

class Reader
{
public:
  
    Reader();

    std::ifstream open(const char* a_fileName);
    std::vector<ConfigData> read(std::ifstream&, char delimeter);

private:

    Parser m_parser;

};

} // namespace smart_home