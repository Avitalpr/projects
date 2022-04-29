#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace smart_home
{

class Parser
{
public:

    std::vector<std::string> extract(std::string& a_record, char a_delimiter);

};

} // namespace smart_home