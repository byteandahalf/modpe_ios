#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"
#include "../minecraftpe/Level.h"
#include "../minecraftpe/ItemInstance.h"
#include "../minecraftpe/Item.h"

ItemInstance* newItemInstance(int, uint8_t, uint16_t);

namespace LevelNS
{
void explode(CScriptVar* jsfunc, void*)
{
	float x =		static_cast<float>(jsfunc->getParameter("x")->getInt()),
		y = 		static_cast<float>(jsfunc->getParameter("y")->getInt()),
		z = 		static_cast<float>(jsfunc->getParameter("z")->getInt()),
		radius =	static_cast<float>(jsfunc->getParameter("radius")->getDouble()),
		maxResistance =	static_cast<float>(jsfunc->getParameter("maxResistance")->getDouble());
	bool makeFire = jsfunc->getParameter("makeFire")->getBool(),
		destroyBlocks = jsfunc->getParameter("destroyBlocks")->getBool();


	if(MCPE_localplayer->level != NULL)
	{
		Level$explode(MCPE_localplayer->level, MCPE_localplayer->region, NULL, Vec3{x, y, z}, radius, makeFire, destroyBlocks, maxResistance);
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

	jsfunc->setReturnVar(new CScriptVar(retval));
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

	jsfunc->setReturnVar(new CScriptVar(retval));
}

void getWorldName(CScriptVar* jsfunc, void*)
{
	jsfunc->setReturnVar(new CScriptVar(MCPE_localplayer->level->data.levelName));
}

void getDifficulty(CScriptVar* jsfunc, void*)
{
	jsfunc->setReturnVar(new CScriptVar(MCPE_localplayer->level->data.difficulty));
}
void setDifficulty(CScriptVar* jsfunc, void*)
{
	int difficulty = jsfunc->getParameter("difficulty")->getInt();

	MCPE_localplayer->level->data.difficulty = difficulty;
}

void getGameMode(CScriptVar* jsfunc, void*)
{
	jsfunc->setReturnVar(new CScriptVar(MCPE_localplayer->level->data.gameType));
}
void setGameMode(CScriptVar* jsfunc, void*)
{
	int gamemode = jsfunc->getParameter("gamemode")->getInt();

	MCPE_localplayer->level->data.gameType = gamemode;
}

void getTime(CScriptVar* jsfunc, void*)
{
	jsfunc->setReturnVar(new CScriptVar(MCPE_localplayer->level->data.time));
}
void setTime(CScriptVar* jsfunc, void*)
{
	int _time = jsfunc->getParameter("time")->getInt();

	MCPE_localplayer->level->data.time = _time;
}
void setChestSlot(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	int itemId = jsfunc->getParameter("itemId")->getInt(),
		count = jsfunc->getParameter("count")->getInt(),
		aux = jsfunc->getParameter("aux")->getInt();

	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	void (*setItem)(BlockEntity*, int, const ItemInstance*) = (void (*)(BlockEntity*, int, const ItemInstance*)) vtable[23];

	// Check if this is a Chest by comparing vtables
	if((uintptr_t)vtable == (uintptr_t)ChestBlockEntity$vtable)
	{
		const ItemInstance* itemStack = newItemInstance(itemId, count, aux);
		setItem(blockEntity, slot, itemStack);
		delete itemStack;
	}
}
void getChestSlot(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	const ItemInstance* (*getItem)(BlockEntity*, int) = (const ItemInstance* (*)(BlockEntity*, int)) vtable[22];
	const ItemInstance* itemStack = getItem(blockEntity, slot);

	int retval = 0;
	if((uintptr_t)vtable == (uintptr_t)ChestBlockEntity$vtable && itemStack != NULL && itemStack->item != NULL)
	{
		retval = itemStack->item->itemId;
	}

	jsfunc->setReturnVar(new CScriptVar(retval));
}
void getChestSlotCount(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	const ItemInstance* (*getItem)(BlockEntity*, int) = (const ItemInstance* (*)(BlockEntity*, int)) vtable[22];
	const ItemInstance* itemStack = getItem(blockEntity, slot);

	int retval = 0;
	if((uintptr_t)vtable == (uintptr_t)ChestBlockEntity$vtable && itemStack != NULL)
	{
		retval = itemStack->count;
	}

	jsfunc->setReturnVar(new CScriptVar(retval));
}
void getChestSlotData(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	const ItemInstance* (*getItem)(BlockEntity*, int) = (const ItemInstance* (*)(BlockEntity*, int)) vtable[22];
	const ItemInstance* itemStack = getItem(blockEntity, slot);

	int retval = 0;
	if((uintptr_t)vtable == (uintptr_t)ChestBlockEntity$vtable && itemStack != NULL)
	{
		retval = itemStack->aux;
	}

	jsfunc->setReturnVar(new CScriptVar(retval));
}
void setFurnaceSlot(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	int itemId = jsfunc->getParameter("itemId")->getInt(),
		count = jsfunc->getParameter("count")->getInt(),
		aux = jsfunc->getParameter("aux")->getInt();

	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	void (*setItem)(BlockEntity*, int, const ItemInstance*) = (void (*)(BlockEntity*, int, const ItemInstance*)) vtable[20];

	// Check if this is a Furnace by comparing vtables
	if((uintptr_t)vtable == (uintptr_t)FurnaceBlockEntity$vtable)
	{
		const ItemInstance* itemStack = newItemInstance(itemId, count, aux);
		setItem(blockEntity, slot, itemStack);
		delete itemStack;
	}
}
void getFurnaceSlot(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	const ItemInstance* (*getItem)(BlockEntity*, int) = (const ItemInstance* (*)(BlockEntity*, int)) vtable[19];
	const ItemInstance* itemStack = getItem(blockEntity, slot);

	int retval = 0;
	if((uintptr_t)vtable == (uintptr_t)FurnaceBlockEntity$vtable && itemStack != NULL && itemStack->item != NULL)
	{
		retval = itemStack->item->itemId;
	}

	jsfunc->setReturnVar(new CScriptVar(retval));
}
void getFurnaceSlotCount(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	const ItemInstance* (*getItem)(BlockEntity*, int) = (const ItemInstance* (*)(BlockEntity*, int)) vtable[19];
	const ItemInstance* itemStack = getItem(blockEntity, slot);

	int retval = 0;
	if((uintptr_t)vtable == (uintptr_t)FurnaceBlockEntity$vtable && itemStack != NULL)
	{
		retval = itemStack->count;
	}

	jsfunc->setReturnVar(new CScriptVar(retval));
}
void getFurnaceSlotData(CScriptVar* jsfunc, void*)
{
	int x = jsfunc->getParameter("x")->getInt(),
		y = jsfunc->getParameter("y")->getInt(),
		z = jsfunc->getParameter("z")->getInt();
	int slot = jsfunc->getParameter("slot")->getInt();
	BlockEntity* blockEntity = BlockSource$getBlockEntity(MCPE_localplayer->region, BlockPos{x, y, z});
	if(blockEntity == NULL)
	{
		return;
	}
	uintptr_t** vtable = *((uintptr_t***) blockEntity);
	const ItemInstance* (*getItem)(BlockEntity*, int) = (const ItemInstance* (*)(BlockEntity*, int)) vtable[19];
	const ItemInstance* itemStack = getItem(blockEntity, slot);

	int retval = 0;
	if((uintptr_t)vtable == (uintptr_t)FurnaceBlockEntity$vtable && itemStack != NULL)
	{
		retval = itemStack->aux;
	}

	jsfunc->setReturnVar(new CScriptVar(retval));
}
};
