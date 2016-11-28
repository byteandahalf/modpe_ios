#include "../TinyJS.h"

#include "../externs.h"

#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"
#include "../minecraftpe/Item.h"
#include "../minecraftpe/ItemInstance.h"

#include <string>

std::string tostr64(uint64_t);


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
	int itemId = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, PlayerInventoryProxy$getSelectedSlot(MCPE_localplayer->inventory).slotId, 0).item->itemId;

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
void getInventorySlot(CScriptVar* jsfunc, void*)
{
	int slotId = jsfunc->getParameter("slotId")->getInt();
	int itemId = PlayerInventoryProxy$getItem(MCPE_localplayer->inventory, slotId, 0).item->itemId;

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
