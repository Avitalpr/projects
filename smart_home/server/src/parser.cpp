#include "parser.hpp"
#include <sstream>


namespace smart_home
{


std::vector<std::string> Parser::extract(std::string& a_record, char a_delimiter)
{
    std::vector<std::string> tokens;
  
    std::stringstream record(a_record);
    std::string token;
    
    while(std::getline(record, token, a_delimiter)) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

} // namespace smart_home