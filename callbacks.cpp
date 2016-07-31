#include <string>
#include <cstdio>

#include "externs.h"

struct LocalPlayer;
struct ItemInstance;
#include "mcpe/common.h"

#include "TinyJS.h"


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

LocalPlayer* (*_LocalPlayer$LocalPlayer)(LocalPlayer*, uintptr_t*, uintptr_t*, uintptr_t*, int, uintptr_t*, uintptr_t*);
LocalPlayer* LocalPlayer$LocalPlayer(LocalPlayer* self, uintptr_t* minecraft, uintptr_t* level, uintptr_t* user, int gamemode, uintptr_t* raknetGUID, uintptr_t* mceUUID)
{
	MCPE_localplayer = self;
	return _LocalPlayer$LocalPlayer(self, minecraft, level, user, gamemode, raknetGUID, mceUUID);
}
