//ModPE.setItem(256, "apple", 0, "Cool thing.", 30);

function useItem(x, y, z, itemId, blockId, side, itemData, blockData)
{
	clientMessage(Item.getMaxStackSize(3));
	Item.setMaxStackSize(3, 12);
	clientMessage(Item.getMaxStackSize(3));
	//Player.setInventorySlot(Player.getSelectedSlotId(), 256, 31, 0);
}

var victim1 = 0;
function attackHook(attacker, victim)
{
	Entity.setCarriedItem(victim, 2, 1, 0);
}

var timer = 300;
function modTick()
{
	if(timer-- <= 0)
	{
		timer = 300;
		clientMessage("Hey dude this is inside a modTick!");
	}
}
