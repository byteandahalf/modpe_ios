#include "../TinyJS.h"

#include "../externs.h"
#include "../queue/SetItemIconTask.h"

#include "../minecraftpe/Item.h"

#include <string>
#include <cstdlib>

namespace ModPENS
{
void setItem(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	std::string icon_name = jsfunc->getParameter("icon_name")->getString();
	int icon_index = jsfunc->getParameter("icon_index")->getInt();
	std::string name = jsfunc->getParameter("name")->getString();
	int stackSize = jsfunc->getParameter("stackSize")->getInt();

	Item* myItemPtr = (Item*) malloc(sizeof(Item));
	Item$Item(myItemPtr, name, itemId - 0x100);
	myItemPtr->maxStackSize = stackSize;

	Item$mItems[itemId] = myItemPtr;

	if(!GRAPHICS_LOADED)
	{
		ModPEQueue::queueTask(new SetItemIconTask(itemId, icon_name, icon_index));
	}
	else
	{
		void (*setIcon)(Item*, const std::string, int) = (void (*)(Item*, const std::string, int))((uintptr_t***) myItemPtr)[0][2];
		setIcon(myItemPtr, icon_name, icon_index);
	}
}
};
