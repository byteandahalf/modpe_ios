#include <string>
#include <cstdio>

#include "TinyJS.h"

#include "externs.h"

struct ItemInstance;
struct MinecraftClient;
#include "minecraftpe/common.h"
#include "minecraftpe/Player.h"



std::string tostr(int);
std::string tostr64(uint64_t);

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

void (*_GameMode$attack)(uintptr_t*, Player*, Entity*);
void GameMode$attack(uintptr_t* self, Player* attacker, Entity* victim)
{
	interpreter->execute("attackHook(0, 0)");//+tostr64(Entity$getUniqueID(attacker))+","+tostr64(Entity$getUniqueID(victim))+");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return;
	}

	_GameMode$attack(self, attacker, victim);
}

LocalPlayer* (*_LocalPlayer$LocalPlayer)(LocalPlayer*, MinecraftClient*, uintptr_t*, uintptr_t*, uintptr_t*, uint64_t);
LocalPlayer* LocalPlayer$LocalPlayer(LocalPlayer* self, MinecraftClient* client, uintptr_t* level, uintptr_t* gametype, uintptr_t* networkID, uint64_t uuid)
{
	MCPE_localplayer = self;
	MCPE_client = client;
	return _LocalPlayer$LocalPlayer(self, client, level, gametype, networkID, uuid);
}
