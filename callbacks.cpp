#include <string>
#include <cstdio>
#include <CydiaSubstrate/CydiaSubstrate.h>

#include "globals.h"

#include "mcpe/common.h"
#include "mcpe/BlockPos.h"
struct BlockSource;
struct ItemInstance;


std::string tostr(int);

bool (*_CreativeMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
bool CreativeMode$useItemOn(uintptr_t* self, uintptr_t* player, ItemInstance& itemStack, const BlockPos& pos, signed char side, uintptr_t* vec)
{
	int x = pos.x, y = pos.y, z = pos.z;
	int itemId = 280; //itemStack.item->id;
	int blockId = 1;

	interpreter->execute("useItem("+tostr(x)+","+tostr(y)+","+tostr(z)+","+tostr(itemId)+","+tostr(blockId)+","+tostr(side)+");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return false;
	}

	return _CreativeMode$useItemOn(self, player, itemStack, pos, side, vec);
}

bool (*_SurvivalMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
bool SurvivalMode$useItemOn(uintptr_t* self, uintptr_t* player, ItemInstance& itemStack, const BlockPos& pos, signed char side, uintptr_t* vec)
{
	int x = pos.x, y = pos.y, z = pos.z;
	int itemId = 280; //itemStack.item->id;
	int blockId = 1;

	interpreter->execute("useItem("+tostr(x)+","+tostr(y)+","+tostr(z)+","+tostr(itemId)+","+tostr(blockId)+","+tostr(side)+");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return false;
	}

	return _SurvivalMode$useItemOn(self, player, itemStack, pos, side, vec);
}

BlockSource* (*_BlockSource$BlockSource)(BlockSource*, uintptr_t*, uintptr_t*, uintptr_t*, bool, bool);
BlockSource* BlockSource$BlockSource(BlockSource* self, uintptr_t* level, uintptr_t* dimension, uintptr_t* chunkSource, bool a, bool b)
{
	MCPE_region = self;
	return _BlockSource$BlockSource(self, level, dimension, chunkSource, a, b);
}
