ModPE.setItem(511, "apple", 0, "Cool thing.", 30);

function useItem(x, y, z, itemId, blockId, side)
{
	clientMessage("Don't harm the environment!");

	if(blockId == 19 && Level.getData(x, y, z) == 0)
	{
		// Damn you Sponge!
		Level.explode(x, y, z, 5.0, true, true, 0.0);
	}
	else if(itemId == 2)
	{
		clientMessage("This is grass!");
	}

	clientMessage(Player.getEntity());
	Entity.setPositionRelative(Player.getEntity(), 0, 10, 0);

	clientMessage(Level.getWorldName());
	//clientMessage(Level.getGameMode());
	clientMessage(Level.getDifficulty());
	clientMessage(Level.getTime());

	//Level.setGameMode(1);
	Level.setDifficulty(0);
	Level.setTime(1000);
}

function attackHook(attacker, victim)
{
	if(Player.getCarriedItem() == 19 && Player.getInventorySlotData(Player.getSelectedSlotId()) == 1)
	{
		Player.clearInventorySlot(Player.getSelectedSlotId());
		clientMessage("Wet sponge!");
	}
	clientMessage(Entity.getPosY(attacker));
	Entity.setPosition(victim, 0, 100, 0);
	Entity.setPositionRelative(attacker, 1, 1, 1);
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
