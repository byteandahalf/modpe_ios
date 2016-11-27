function useItem(x, y, z, itemId, blockId, side)
{
	clientMessage("Don't harm the environment!");

	if(Level.getTile(x, y, z) == 19 && Level.getData(x, y, z) == 0)
	{
		// Damn you Sponge!
		Level.explode(x, y, z, 5.0, false, true, 0.0);
	}
	else
	{
		Level.setTile(x, y, z, 1, 0);
	}

	//preventDefault();

	clientMessage(Level.getWorldName());
	clientMessage(Level.getGameMode());
	clientMessage(Level.getDifficulty());
	clientMessage(Level.getTime());

	Level.setGameMode(1);
	Level.setDifficulty(0);
	Level.setTime(1000);
}

function attackHook(attacker, victim)
{
	preventDefault();
	clientMessage("Don't hurt the animals!");
}
