#include <iostream>

#include "../externs.h"
#include "../mcpe/common.h"
#include "../mcpe/LocalPlayer.h"

void print(CScriptVar* jsfunc, void*)
{
	// TODO: make this an iOS alert
	std::cout << jsfunc->getParameter("text")->getString() << "\n";
}

void setTile(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	uint8_t blockId = jsfunc->getParameter("blockId")->getInt(),
		data = jsfunc->getParameter("data")->getInt();

	BlockSource$setBlockAndData(MCPE_localplayer->region, x, y, z, FullBlock{blockId, data}, 2);
}

void preventDefault(CScriptVar* jsfunc, void*)
{
	PREVENTDEFAULT = true;
}
