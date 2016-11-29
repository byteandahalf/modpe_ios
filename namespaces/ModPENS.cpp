#include "../TinyJS.h"

#include "../externs.h"
#include "../request/ModPESetItemRequest.h"

#include "../minecraftpe/Item.h"

#include <string>
#include <cstdlib>

namespace ModPENS
{
void setItem(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	std::string texture_name = jsfunc->getParameter("texture_name")->getString();
	int texture_index = jsfunc->getParameter("texture_index")->getInt();
	std::string name = jsfunc->getParameter("name")->getString();
	int stackSize = jsfunc->getParameter("stackSize")->getInt();

	// allocate the new Item, and use MCPE's contructor, TODO: localize name
	Item* myItemPtr = (Item*) malloc(sizeof(Item));
	Item$Item(myItemPtr, name, itemId - 0x100);
	// if the Item texture atlas has been initialized, set the icon now via vtable
	if(*Item$mTextureAtlas)
	{
		void (*setIcon)(Item*, const std::string&, int) = (void (*)(Item*, const std::string&, int))((uintptr_t***) myItemPtr)[0][2];
		setIcon(myItemPtr, texture_name, texture_index);
	}
	// otherwise, queue the action for later (after mTextureAtlas is initialized)
	else
	{
		ModPESetItemRequest::request(new ModPESetIconRequest(myItemPtr, texture_name, texture_index));
	}
	// set the maxStackSize
	myItemPtr->maxStackSize = stackSize;
	// Add it to MCPE's global Items list, TODO: also add to mItemLookupMap
	Item$mItems[itemId] = myItemPtr;
}
};
