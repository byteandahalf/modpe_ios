#include "../TinyJS.h"

#include "../externs.h"

#include "../minecraftpe/ItemInstance.h"

const ItemInstance* newItemInstance(int, uint8_t, uint16_t);

namespace ItemNS
{
void setMaxStackSize(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	uint8_t stackSize = jsfunc->getParameter("stackSize")->getInt();
	Item* itemPtr = Item$mItems[itemId];

	if(itemPtr != NULL)
	{
		void (*setMaxStackSize)(Item*, uint8_t) = (void (*)(Item*, uint8_t))((uintptr_t***) itemPtr)[0][4];
		setMaxStackSize(itemPtr, stackSize);
	}
}
void getMaxStackSize(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	Item* itemPtr = Item$mItems[itemId];
	int retval = 0;

	if(itemPtr != NULL)
	{
		int (*getMaxStackSize)(Item*, const ItemInstance*) = (int (*)(Item*, const ItemInstance*))((uintptr_t***) itemPtr)[0][49];
		// TODO: this is incorrect for BucketItem since data is hardcoded as 0
		// (always returns 16 when full Bucket is 1)
		const ItemInstance* itemStack = newItemInstance(itemId, 1, 0);
		retval = getMaxStackSize(itemPtr, itemStack);
		delete itemStack;
	}
	jsfunc->setReturnVar(new CScriptVar(retval));
}
};
