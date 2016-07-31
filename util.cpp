#include <string>
#include <sstream>

std::string tostr(int num)
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
