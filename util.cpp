#include <string>
#include <sstream>

std::string tostr(int num)
{
    std::stringstream ss;
    ss << num;

    return ss.str();
}
