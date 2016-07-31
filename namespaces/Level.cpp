#include "../TinyJS.h"

#include "../externs.h"
#include "../mcpe/common.h"
#include "../mcpe/Player.h"

namespace LevelNS
{
void setTile(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	uint8_t blockId = jsfunc->getParameter("blockId")->getInt(),
		data = jsfunc->getParameter("data")->getInt();

	BlockSource$setBlockAndData(MCPE_localplayer->region, x, y, z, FullBlock{blockId, data}, 2);
}

void getTile(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();

	int retval = BlockSource$getBlockAndData(MCPE_localplayer->region, BlockPos{x, y, z}).blockId;

	jsfunc->setReturnVar(new CScriptVar(retval));
}

void getData(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();

	int retval = BlockSource$getBlockAndData(MCPE_localplayer->region, BlockPos{x, y, z}).data;

	jsfunc->setReturnVar(new CScriptVar(retval));
}
};
