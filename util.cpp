#include <string>
#include <sstream>
#include <stdint.h>

std::string tostr(int num)
{
    std::stringstream ss;
    ss << num;

    return ss.str();
}

std::string tostr64(uint64_t num)
{
    std::stringstream ss;
    ss << num;

    return ss.str();
}

uint64_t strToU64(const std::string& str)
{
	return std::stoull(str, NULL, 0);
}

void VirtualHook(uintptr_t** vtable, short offset, void* hook, void** real)
{
	*real = (void*) vtable[offset];
	vtable[offset] = (uintptr_t*) hook;
}
