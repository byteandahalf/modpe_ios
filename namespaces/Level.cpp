#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"

namespace LevelNS
{
void explode(CScriptVar* jsfunc, void*)
{
	float x =		static_cast<float>(jsfunc->getParameter("x")->getInt()),
		y = 		static_cast<float>(jsfunc->getParameter("y")->getInt()),
		z = 		static_cast<float>(jsfunc->getParameter("z")->getInt());
	float radius =	static_cast<float>(jsfunc->getParameter("radius")->getDouble());

	if(MCPE_localplayer->level != NULL)
	{
		// Explode:		Level, Region, Entity(NULL for none), radius, makeFire, destroyBlocks, idk
		Level$explode(MCPE_localplayer->level, MCPE_localplayer->region, NULL, Vec3{x, y, z}, radius, false, true, 10.0F);
	}
}

void setTile(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	uint8_t blockId = jsfunc->getParameter("blockId")->getInt(),
		data = jsfunc->getParameter("data")->getInt();

	if(MCPE_localplayer->region != NULL)
	{
		BlockSource$setBlockAndData(MCPE_localplayer->region, x, y, z, FullBlock{blockId, data}, 2);
	}
}

void getTile(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();

	int retval = 0;
	if(MCPE_localplayer->region != NULL)
	{
		retval = BlockSource$getBlockAndData(MCPE_localplayer->region, BlockPos{x, y, z}).blockId;
	}

	jsfunc->setReturnVar(new CScriptVar((long) retval));
}

void getData(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();

	int retval = 0;
	if(MCPE_localplayer->region != NULL)
	{
		retval = BlockSource$getBlockAndData(MCPE_localplayer->region, BlockPos{x, y, z}).data;
	}

	jsfunc->setReturnVar(new CScriptVar((long) retval));
}
};
