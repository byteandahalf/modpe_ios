#include "TinyJS.h"

#include "externs.h"
#include "queue/ModPEQueue.h"

struct ItemInstance;
struct MinecraftClient;
#include "minecraftpe/common.h"
#include "minecraftpe/Player.h"
#include "minecraftpe/ItemInstance.h"
#include "minecraftpe/Item.h"

#include <string>
#include <cstdio>

void ModPE_initScripts();
std::string tostr(int);
std::string tostr64(uint64_t);


bool (*_CreativeMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance*, const BlockPos&, signed char, uintptr_t*);
bool CreativeMode$useItemOn(uintptr_t* self, uintptr_t* player, ItemInstance* itemStack, const BlockPos& pos, signed char side, uintptr_t* vec)
{
	int x = pos.x, y = pos.y, z = pos.z;
	int itemId = 0;
	int itemData = 0;
	if(itemStack != NULL && itemStack->item != NULL)
	{
		itemId = itemStack->item->itemId;
		itemData = itemStack->aux;
	}

	FullBlock fullBlock = BlockSource$getBlockAndData(MCPE_localplayer->region, pos);
	int blockId = fullBlock.blockId;
	int blockData = fullBlock.data;

	interpreter->execute("useItem("+tostr(x)+","+tostr(y)+","+tostr(z)+","+tostr(itemId)+","+tostr(blockId)+","+tostr(side)+","+tostr(itemData)+","+tostr(blockData)+");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return false;
	}

	return _CreativeMode$useItemOn(self, player, itemStack, pos, side, vec);
}
bool (*_SurvivalMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance*, const BlockPos&, signed char, uintptr_t*);
bool SurvivalMode$useItemOn(uintptr_t* self, uintptr_t* player, ItemInstance* itemStack, const BlockPos& pos, signed char side, uintptr_t* vec)
{
	int x = pos.x, y = pos.y, z = pos.z;
	int itemId = 0;
	int itemData = 0;
	if(itemStack != NULL && itemStack->item != NULL)
	{
		itemId = itemStack->item->itemId;
		itemData = itemStack->aux;
	}
	FullBlock fullBlock = BlockSource$getBlockAndData(MCPE_localplayer->region, pos);
	int blockId = fullBlock.blockId;
	int blockData = fullBlock.data;

	interpreter->execute("useItem("+tostr(x)+","+tostr(y)+","+tostr(z)+","+tostr(itemId)+","+tostr(blockId)+","+tostr(side)+","+tostr(itemData)+","+tostr(blockData)+");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return false;
	}

	return _SurvivalMode$useItemOn(self, player, itemStack, pos, side, vec);
}

void (*_CreativeMode$attack)(uintptr_t*, Player*, Entity*);
void CreativeMode$attack(uintptr_t* self, Player* attacker, Entity* victim)
{
	interpreter->execute("attackHook(\""+tostr64(Entity$getUniqueID(attacker))+"\",\""+tostr64(Entity$getUniqueID(victim))+"\");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return;
	}

	_CreativeMode$attack(self, attacker, victim);
}
void (*_SurvivalMode$attack)(uintptr_t*, Player*, Entity*);
void SurvivalMode$attack(uintptr_t* self, Player* attacker, Entity* victim)
{
	interpreter->execute("attackHook(\""+tostr64(Entity$getUniqueID(attacker))+"\",\""+tostr64(Entity$getUniqueID(victim))+"\");");

	if(PREVENTDEFAULT)
	{
		PREVENTDEFAULT = false;
		return;
	}

	_SurvivalMode$attack(self, attacker, victim);
}

void (*_CreativeMode$tick)(uintptr_t*);
void CreativeMode$tick(uintptr_t* self)
{
	interpreter->execute("modTick();");

	_CreativeMode$tick(self);
}
void (*_SurvivalMode$tick)(uintptr_t*);
void SurvivalMode$tick(uintptr_t* self)
{
	interpreter->execute("modTick();");

	_SurvivalMode$tick(self);
}

LocalPlayer* (*_LocalPlayer$LocalPlayer)(LocalPlayer*, MinecraftClient*, uintptr_t*, uintptr_t*, uintptr_t*, uint64_t);
LocalPlayer* LocalPlayer$LocalPlayer(LocalPlayer* self, MinecraftClient* client, uintptr_t* level, uintptr_t* gametype, uintptr_t* networkID, uint64_t uuid)
{
	MCPE_localplayer = self;
	MCPE_client = client;
	return _LocalPlayer$LocalPlayer(self, client, level, gametype, networkID, uuid);
}

void (*_MinecraftClient$update)(MinecraftClient*);
void MinecraftClient$update(MinecraftClient* self)
{
	_MinecraftClient$update(self);
	if(SCRIPTS_NEED_INIT)
	{
		SCRIPTS_NEED_INIT = false;
		ModPE_initScripts();
	}
}

void (*_MinecraftClient$onResourcesLoaded)(MinecraftClient*);
void MinecraftClient$onResourcesLoaded(MinecraftClient* self)
{
	_MinecraftClient$onResourcesLoaded(self);

	GRAPHICS_LOADED = true;
	ModPEQueue::doTasks(TaskType::TASK_SETICON);
}
