#include "../TinyJS.h"

#include "../externs.h"

namespace ItemNS
{
void setMaxStackSize(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	uint8_t stackSize = jsfunc->getParameter("stackSize")->getInt();
	Item* itemPtr = Item$mItems[itemId];

	if(itemPtr != NULL)
	{
		void (*_setMaxStackSize)(Item*, uint8_t) = (void (*)(Item*, uint8_t))((uintptr_t***) itemPtr)[0][4];
		_setMaxStackSize(itemPtr, stackSize);
	}
}
};
