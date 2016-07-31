#include <string>
#include <sstream>
#include <stdint.h>

std::string tostr(uint64_t num)
{
    std::stringstream ss;
    ss << num;

    return ss.str();
}

void VirtualHook(uintptr_t** vtable, short offset, void* hook, void** real)
{
	*real = (void*) vtable[offset];
	vtable[offset] = (uintptr_t*) hook;
}
