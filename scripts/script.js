//ModPE.setItem(256, "apple", 0, "Cool thing.", 30);

function useItem(x, y, z, itemId, blockId, side, itemData, blockData)
{
	if(blockId == 54)
	{
		clientMessage(Level.getChestSlot(x, y, z, 0));
		clientMessage(Level.getChestSlotCount(x, y, z, 0));
		clientMessage(Level.getChestSlotData(x, y, z, 0));
		Level.setChestSlot(x, y, z, 0, 318, 34, 0);
	}
	if(blockId == 61)
	{
		clientMessage(Level.getFurnaceSlot(x, y, z, 0));
		clientMessage(Level.getFurnaceSlotCount(x, y, z, 0));
		clientMessage(Level.getFurnaceSlotData(x, y, z, 0));
		Level.setFurnaceSlot(x, y, z, 0, 19, 16, 1);
	}
	if(blockId == 63 || blockId == 68)
	{
		clientMessage(Level.getSignText(x, y, z, 1));
		Level.setSignText(x, y, z, 1, "Level.setSignText");
		Level.setSignText(x, y, z, 2, "and getSignText");
		Level.setSignText(x, y, z, 3, "now on iOS!");
	}
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
		//clientMessage("Hey dude this is inside a modTick!");
	}
}
