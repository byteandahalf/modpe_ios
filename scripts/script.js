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
	//Entity.setPosition(Player.getEntity(), 0, 100, 0);

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
	// currently this crashes.
	Entity.setPosition(victim, 0, 100, 0);
}
