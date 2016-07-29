#include <iostream>

#include "../globals.h"
#include "../mcpe/common.h"

void print(CScriptVar* pars, void*)
{
	// TODO: make this an iOS alert
	std::cout << pars->getParameter("text")->getString() << "\n";
}

void setTile(CScriptVar* pars, void*)
{
	int x = pars->getParameter("x")->getInt(),
		y = pars->getParameter("y")->getInt(),
		z = pars->getParameter("z")->getInt();
	uint8_t blockId = pars->getParameter("blockId")->getInt(),
		data = pars->getParameter("meta")->getInt();

	BlockSource$setBlockAndData(MCPE_region, x, y, z, FullBlock{blockId, data}, 2);
}

void preventDefault(CScriptVar* pars, void*)
{
	PREVENTDEFAULT = true;
}
