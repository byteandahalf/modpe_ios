//ModPE.setItem(511, "apple", 0, "Cool thing.", 30);

function useItem(x, y, z, itemId, blockId, side, itemData, blockData)
{
	Player.addItemInventory(19, 1, 0);
}

function attackHook(attacker, victim)
{
	if(Player.getCarriedItem() == 19 && Player.getInventorySlotData(Player.getSelectedSlotId()) == 1)
	{
		Player.clearInventorySlot(Player.getSelectedSlotId());
		clientMessage("Wet sponge!");
	}
	clientMessage("Dude.");
	Entity.setVelX(victim, 3.0);
	Entity.setPositionRelative(attacker, 1, 1, 1);
	Player.setInventorySlot(Player.getSelectedSlotId(), 256, 30, 100);
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
