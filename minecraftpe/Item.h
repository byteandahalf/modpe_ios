#ifndef __MCPE_ITEM_H
#define __MCPE_ITEM_H

struct Item
{
	uintptr_t** vtable; // 0
	std::string atlas; // 8
	char filler[14]; // 32
	short itemId; // 46
};

#endif
