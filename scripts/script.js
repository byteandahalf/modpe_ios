function useItem(x, y, z, itemId, blockId, side)
{
	clientMessage("Don't harm the environment!");

	if(Level.getTile(x, y, z) == 19 && Level.getData(x, y, z) == 0)
	{
		// Damn you Sponge!
		Level.explode(x, y, z, 5.0);
	}
	else
	{
		Level.setTile(x, y, z, 19, 0);
	}
}

function attackHook(attacker, victim)
{
	preventDefault();
	clientMessage("Don't hurt the animals!");
}
