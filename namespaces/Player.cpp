#include "../TinyJS.h"

#include "../externs.h"

#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"
#include "../minecraftpe/Item.h"
#include "../minecraftpe/ItemInstance.h"

#include <string>

std::string tostr64(uint64_t);
ItemInstance* newItemInstance(int, uint8_t, uint16_t);


namespace PlayerNS
{
void getEntity(CScriptVar* jsfunc, void*)
{
	jsfunc->setReturnVar(new CScriptVar(tostr64(Entity$getUniqueID(MCPE_localplayer))));
}

void clearInventorySlot(CScriptVar* jsfunc, void*)
{
	int slot = jsfunc->getParameter("slotId")->getInt();

	PlayerInventoryProxy$clearSlot(MCPE_localplayer->inventory, slot, 0);
}
void getSelectedSlotId(CScriptVar* jsfunc, void*)
{
	int slotId = PlayerInventoryProxy$getSelectedSlot(MCPE_localplayer->inventory).slotId;

	jsfunc->setReturnVar(new CScriptVar(slotId));
}
void getCarriedItem(CScriptVar* jsfunc, void*)
{
	const ItemInstance& itemStack = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, PlayerInventoryProxy$getSelectedSlot(MCPE_localplayer->inventory).slotId, 0);
	int itemId = 0;
	if(itemStack.item != NULL)
	{
		itemId = itemStack.item->itemId;
	}

	jsfunc->setReturnVar(new CScriptVar(itemId));
}
void getCarriedItemCount(CScriptVar* jsfunc, void*)
{
	int count = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, PlayerInventoryProxy$getSelectedSlot(MCPE_localplayer->inventory).slotId, 0).count;

	jsfunc->setReturnVar(new CScriptVar(count));
}
void getCarriedItemData(CScriptVar* jsfunc, void*)
{
	int aux = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, PlayerInventoryProxy$getSelectedSlot(MCPE_localplayer->inventory).slotId, 0).aux;

	jsfunc->setReturnVar(new CScriptVar(aux));
}
void addItemInventory(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	int count = jsfunc->getParameter("count")->getInt();
	int aux = jsfunc->getParameter("aux")->getInt();

	ItemInstance* itemStack = newItemInstance(itemId, count, aux);
	if(itemStack != NULL)
	{
		PlayerInventoryProxy$add(MCPE_localplayer->inventory, *itemStack, true);
		// PlayerInventoryProxy::add clones the ItemInstance, so it's safe to deallocate ours.
		delete itemStack;
	}
}
void setInventorySlot(CScriptVar* jsfunc, void*)
{
	int slotId = jsfunc->getParameter("slotId")->getInt();
	int itemId = jsfunc->getParameter("itemId")->getInt();
	int count = jsfunc->getParameter("count")->getInt();
	int aux = jsfunc->getParameter("aux")->getInt();

	if(((slotId > PlayerInventoryProxy$getLinkedSlotsCount(MCPE_localplayer->inventory)) && slotId >= 0)
		|| (slotId = PlayerInventoryProxy$getLinkedSlot(MCPE_localplayer->inventory, slotId)) >= 0)
	{
		ItemInstance* itemStack = newItemInstance(itemId, count, aux);
		if(itemStack != NULL)
		{
			PlayerInventoryProxy$replaceSlot(MCPE_localplayer->inventory, slotId, *itemStack);
			delete itemStack;
		}
	}
}
void getInventorySlot(CScriptVar* jsfunc, void*)
{
	int slotId = jsfunc->getParameter("slotId")->getInt();
	const ItemInstance& itemStack = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, slotId, 0);
	int itemId = 0;
	if(itemStack.item != NULL)
	{
		itemId = itemStack.item->itemId;
	}

	jsfunc->setReturnVar(new CScriptVar(itemId));
}
void getInventorySlotCount(CScriptVar* jsfunc, void*)
{
	int slotId = jsfunc->getParameter("slotId")->getInt();
	int count = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, slotId, 0).count;

	jsfunc->setReturnVar(new CScriptVar(count));
}
void getInventorySlotData(CScriptVar* jsfunc, void*)
{
	int slotId = jsfunc->getParameter("slotId")->getInt();
	int aux = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, slotId, 0).aux;

	jsfunc->setReturnVar(new CScriptVar(aux));
}
};
