#include <sys/stat.h>
#include <cstdio>
#include <iostream>

#include <Forklift/Forklift.h>

#include "TinyJS.h"

//constants
#define GAMEMODE_USEITEMON_OFFSET 13
#define GAMEMODE_ATTACK_OFFSET 15
#define GAMEMODE_TICK_OFFSET 17

//forward decs for prototypes
struct LocalPlayer;
struct MinecraftClient;
struct Level;
struct ItemInstance;
struct BlockPos;
struct FullBlock;
struct Player;
struct Entity;

#include "externs.h" // for function pointers

//callback prototypes
extern bool (*_CreativeMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance*, const BlockPos&, signed char, uintptr_t*);
bool CreativeMode$useItemOn(uintptr_t*, uintptr_t*, ItemInstance*, const BlockPos&, signed char, uintptr_t*);
extern bool (*_SurvivalMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance*, const BlockPos&, signed char, uintptr_t*);
bool SurvivalMode$useItemOn(uintptr_t*, uintptr_t*, ItemInstance*, const BlockPos&, signed char, uintptr_t*);
extern void (*_CreativeMode$attack)(uintptr_t*, Player*, Entity*);
void CreativeMode$attack(uintptr_t*, Player*, Entity*);
extern void (*_SurvivalMode$attack)(uintptr_t*, Player*, Entity*);
void SurvivalMode$attack(uintptr_t*, Player*, Entity*);
extern void (*_CreativeMode$tick)(uintptr_t*);
void CreativeMode$tick(uintptr_t*);
extern void (*_SurvivalMode$tick)(uintptr_t*);
void SurvivalMode$tick(uintptr_t*);
extern LocalPlayer* (*_LocalPlayer$LocalPlayer)(LocalPlayer*, MinecraftClient*, uintptr_t*, uintptr_t*, uintptr_t*, uint64_t);
LocalPlayer* LocalPlayer$LocalPlayer(LocalPlayer*, MinecraftClient*, uintptr_t*, uintptr_t*, uintptr_t*, uint64_t);
extern void (*_MinecraftClient$update)(MinecraftClient*);
void MinecraftClient$update(MinecraftClient*);
extern void (*_MinecraftClient$onResourcesLoaded)(MinecraftClient*);
void MinecraftClient$onResourcesLoaded(MinecraftClient*);
/*
*	ModPE calls
*/
//top-level
void print(CScriptVar*, void*);
void clientMessage(CScriptVar*, void*);
void preventDefault(CScriptVar*, void*);
//Level
namespace LevelNS
{
	void explode(CScriptVar*, void*);
	void setTile(CScriptVar*, void*);
	void getTile(CScriptVar*, void*);
	void getData(CScriptVar*, void*);
	void getWorldName(CScriptVar*, void*);
	void getDifficulty(CScriptVar*, void*);
	void setDifficulty(CScriptVar*, void*);
	void getGameMode(CScriptVar*, void*);
	void setGameMode(CScriptVar*, void*);
	void getTime(CScriptVar*, void*);
	void setTime(CScriptVar*, void*);
	void setChestSlot(CScriptVar*, void*);
	void getChestSlot(CScriptVar*, void*);
	void getChestSlotCount(CScriptVar*, void*);
	void getChestSlotData(CScriptVar*, void*);
	void setFurnaceSlot(CScriptVar*, void*);
	void getFurnaceSlot(CScriptVar*, void*);
	void getFurnaceSlotCount(CScriptVar*, void*);
	void getFurnaceSlotData(CScriptVar*, void*);
};
//Entity
namespace EntityNS
{
	void getEntityTypeId(CScriptVar*, void*);
	void remove(CScriptVar*, void*);
	void getVelX(CScriptVar*, void*);
	void getVelY(CScriptVar*, void*);
	void getVelZ(CScriptVar*, void*);
	void setVelX(CScriptVar*, void*);
	void setVelY(CScriptVar*, void*);
	void setVelZ(CScriptVar*, void*);
	void getPosX(CScriptVar*, void*);
	void getPosY(CScriptVar*, void*);
	void getPosZ(CScriptVar*, void*);
	void setPosition(CScriptVar*, void*);
	void setPositionRelative(CScriptVar*, void*);
	void setFireTicks(CScriptVar*, void*);
	void rideAnimal(CScriptVar*, void*);
	void setCarriedItem(CScriptVar*, void*);
};
//Player
namespace PlayerNS
{
	void getEntity(CScriptVar*, void*);
	void clearInventorySlot(CScriptVar*, void*);
	void getSelectedSlotId(CScriptVar*, void*);
	void getCarriedItem(CScriptVar*, void*);
	void getCarriedItemCount(CScriptVar*, void*);
	void getCarriedItemData(CScriptVar*, void*);
	void addItemInventory(CScriptVar*, void*);
	void setInventorySlot(CScriptVar*, void*);
	void getInventorySlot(CScriptVar*, void*);
	void getInventorySlotCount(CScriptVar*, void*);
	void getInventorySlotData(CScriptVar*, void*);
};
//ModPE
namespace ModPENS
{
	void setItem(CScriptVar*, void*);
};
//Item
namespace ItemNS
{
	void setMaxStackSize(CScriptVar*, void*);
	void getMaxStackSize(CScriptVar*, void*);
}

void ModPE_initScripts()
{
	// currently just loads a test script
	const char* script = "var/mobile/modpe/script.js";

	struct stat results;
	if(stat(script, &results) != 0)
	{
		printf("Cannot stat file! '%s'\n", script);
		return;
	}

	int size = results.st_size;
	FILE* file = fopen(script, "rb");

	if(!file)
	{
		printf("Unable to open file! '%s'\n", script);
		return;
	}

	char* buffer = new char[size + 1];
	long actualRead = fread(buffer, 1, size, file);
	buffer[actualRead] = 0;
	buffer[size] = 0;
	fclose(file);

	try
	{
		// run top-level script calls and variable declarations.
		interpreter->execute(buffer);
	}
	catch (CScriptException* e)
	{
		printf("ERROR: %s\n", e->text.c_str());
	}

	delete[] buffer;
}


void registerScriptCalls()
{
	interpreter->addNative("function print(text)", print, interpreter);
	interpreter->addNative("function clientMessage(text)", clientMessage, interpreter);
	interpreter->addNative("function preventDefault()", preventDefault, interpreter);

	interpreter->addNative("function Level.explode(x, y, z, radius, makeFire, destroyBlocks, maxResistance)", LevelNS::explode, interpreter);
	interpreter->addNative("function Level.setTile(x, y, z, blockId, data)", LevelNS::setTile, interpreter);
	interpreter->addNative("function Level.getTile(x, y, z)", LevelNS::getTile, interpreter);
	interpreter->addNative("function Level.getData(x, y, z)", LevelNS::getData, interpreter);
	interpreter->addNative("function Level.getWorldName()", LevelNS::getWorldName, interpreter);
	interpreter->addNative("function Level.getDifficulty()", LevelNS::getDifficulty, interpreter);
	interpreter->addNative("function Level.setDifficulty(difficulty)", LevelNS::setDifficulty, interpreter);
	//interpreter->addNative("function Level.getGameMode()", LevelNS::getGameMode, interpreter);
	//interpreter->addNative("function Level.setGameMode(gamemode)", LevelNS::setGameMode, interpreter);
	interpreter->addNative("function Level.getTime()", LevelNS::getTime, interpreter);
	interpreter->addNative("function Level.setTime(time)", LevelNS::setTime, interpreter);
	interpreter->addNative("function Level.setChestSlot(x, y, z, slot, itemId, count, aux)", LevelNS::setChestSlot, interpreter);
	interpreter->addNative("function Level.getChestSlot(x, y, z, slot)", LevelNS::getChestSlot, interpreter);
	interpreter->addNative("function Level.getChestSlotCount(x, y, z, slot)", LevelNS::getChestSlotCount, interpreter);
	interpreter->addNative("function Level.getChestSlotData(x, y, z, slot)", LevelNS::getChestSlotData, interpreter);
	interpreter->addNative("function Level.setFurnaceSlot(x, y, z, slot, itemId, count, aux)", LevelNS::setFurnaceSlot, interpreter);
	interpreter->addNative("function Level.getFurnaceSlot(x, y, z, slot)", LevelNS::getFurnaceSlot, interpreter);
	interpreter->addNative("function Level.getFurnaceSlotCount(x, y, z, slot)", LevelNS::getFurnaceSlotCount, interpreter);
	interpreter->addNative("function Level.getFurnaceSlotData(x, y, z, slot)", LevelNS::getFurnaceSlotData, interpreter);

	interpreter->addNative("function Entity.getEntityTypeId(uniqueID)", EntityNS::getEntityTypeId, interpreter);
	interpreter->addNative("function Entity.remove(uniqueID)", EntityNS::remove, interpreter);
	interpreter->addNative("function Entity.getX(uniqueID)", EntityNS::getPosX, interpreter);
	interpreter->addNative("function Entity.getY(uniqueID)", EntityNS::getPosY, interpreter);
	interpreter->addNative("function Entity.getZ(uniqueID)", EntityNS::getPosZ, interpreter);
	interpreter->addNative("function Entity.setPosition(uniqueID, x, y, z)", EntityNS::setPosition, interpreter);
	interpreter->addNative("function Entity.setPositionRelative(uniqueID, x, y, z)", EntityNS::setPositionRelative, interpreter);
	interpreter->addNative("function Entity.getVelX(uniqueID)", EntityNS::getVelX, interpreter);
	interpreter->addNative("function Entity.getVelY(uniqueID)", EntityNS::getVelY, interpreter);
	interpreter->addNative("function Entity.getVelZ(uniqueID)", EntityNS::getVelZ, interpreter);
	interpreter->addNative("function Entity.setVelX(uniqueID, velocity)", EntityNS::setVelX, interpreter);
	interpreter->addNative("function Entity.setVelY(uniqueID, velocity)", EntityNS::setVelY, interpreter);
	interpreter->addNative("function Entity.setVelZ(uniqueID, velocity)", EntityNS::setVelZ, interpreter);
	interpreter->addNative("function Entity.setFireTicks(uniqueID, ticks)", EntityNS::setFireTicks, interpreter);
	interpreter->addNative("function Entity.rideAnimal(rider, ride)", EntityNS::rideAnimal, interpreter);
	interpreter->addNative("function Entity.setCarriedItem(uniqueID, itemId, count, aux)", EntityNS::setCarriedItem, interpreter);

	interpreter->addNative("function Player.getEntity()", PlayerNS::getEntity, interpreter);
	interpreter->addNative("function Player.clearInventorySlot(slotId)", PlayerNS::clearInventorySlot, interpreter);
	interpreter->addNative("function Player.getSelectedSlotId()", PlayerNS::getSelectedSlotId, interpreter);
	interpreter->addNative("function Player.getCarriedItem()", PlayerNS::getCarriedItem, interpreter);
	interpreter->addNative("function Player.getCarriedItemCount()", PlayerNS::getCarriedItemCount, interpreter);
	interpreter->addNative("function Player.getCarriedItemData()", PlayerNS::getCarriedItemData, interpreter);
	interpreter->addNative("function Player.addItemInventory(itemId, count, aux)", PlayerNS::addItemInventory, interpreter);
	interpreter->addNative("function Player.setInventorySlot(slotId, itemId, count, aux)", PlayerNS::setInventorySlot, interpreter);
	interpreter->addNative("function Player.getInventorySlot(slotId)", PlayerNS::getInventorySlot, interpreter);
	interpreter->addNative("function Player.getInventorySlotCount(slotId)", PlayerNS::getInventorySlotCount, interpreter);
	interpreter->addNative("function Player.getInventorySlotData(slotId)", PlayerNS::getInventorySlotData, interpreter);

	interpreter->addNative("function ModPE.setItem(itemId, icon_name, icon_index, name, stackSize)", ModPENS::setItem, interpreter);

	interpreter->addNative("function Item.setMaxStackSize(itemId, stackSize)", ItemNS::setMaxStackSize, interpreter);
	interpreter->addNative("function Item.getMaxStackSize(itemId)", ItemNS::getMaxStackSize, interpreter);
}


void VirtualHook(uintptr_t** vtable, short offset, void* hook, void** real);

void initPointers()
{
	// currently only arm64 support
	FLHookSymbol(Level$explode, FLAddress(0x00000000 | 1, 0x1007a9118));
	FLHookSymbol(BlockSource$setBlockAndData, FLAddress(0x00000000 | 1, 0x10079bc80));
	FLHookSymbol(BlockSource$getBlockAndData, FLAddress(0x00000000 | 1, 0x10079a1fc));
	FLHookSymbol(BlockSource$getBlockEntity, FLAddress(0x00000000 | 1, 0x10079c080));
	FLHookSymbol(Entity$getUniqueID, FLAddress(0x00000000 | 1, 0x100657960));
	FLHookSymbol(Level$fetchEntity, FLAddress(0x00000000 | 1, 0x1007a8920));
	FLHookSymbol(GuiData$addMessage, FLAddress(0x00000000 | 1, 0x100108428));
	FLHookSymbol(PlayerInventoryProxy$getSelectedSlot, FLAddress(0x00000000 | 1, 0x1007168c8));
	FLHookSymbol(PlayerInventoryProxy$getItem, FLAddress(0x00000000 | 1, 0x100716884));
	FLHookSymbol(PlayerInventoryProxy$add, FLAddress(0x00000000 | 1, 0x1007161fc));
	FLHookSymbol(PlayerInventoryProxy$getLinkedSlotsCount, FLAddress(0x00000000 | 1, 0x1007161f4));
	FLHookSymbol(PlayerInventoryProxy$getLinkedSlot, FLAddress(0x00000000 | 1, 0x1007161c4));
	FLHookSymbol(PlayerInventoryProxy$replaceSlot, FLAddress(0x00000000 | 1, 0x100716688));
	FLHookSymbol(PlayerInventoryProxy$clearSlot, FLAddress(0x00000000 | 1, 0x10071665c));
	FLHookSymbol(Item$Item, FLAddress(0x00000000 | 1, 0x10074689c));
	FLHookSymbol(ItemInstance$fromItem, FLAddress(0x00000000 | 1, 0x1007568e8));
	FLHookSymbol(ItemInstance$operator_equals, FLAddress(0x00000000 | 1, 0x100757b68));

	FLHookSymbol(Item$mItems, FLAddress(0x00000000, 0x1012ae238));

	//0x1012ae208 Item::mTextureAtlas
	//0x1007160fc selectSlot(int, ContainerID)
	//0x1007a76f0 Level::playSound
	//0x1007487d4 defineItem(const char*, int&)
	//0x1012ae210 Item::mItemLookupMap
	//0x10074dc34 map<std::string, std::pair<const std::string, std::unique_ptr<Item>>>::operator[](const std::string&)

	FLHookSymbol(FurnaceBlockEntity$vtable, FLAddress(0x00000000, 0x1011632c8));
	FLHookSymbol(ChestBlockEntity$vtable, FLAddress(0x00000000, 0x101162a38));
	FLHookSymbol(CreativeMode$vtable, FLAddress(0x00000000, 0x1011D7C78));
	FLHookSymbol(SurvivalMode$vtable, FLAddress(0x00000000, 0x10113DDC0));
	VirtualHook(CreativeMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &CreativeMode$useItemOn, (void**) &_CreativeMode$useItemOn);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &SurvivalMode$useItemOn, (void**) &_SurvivalMode$useItemOn);
	VirtualHook(CreativeMode$vtable, GAMEMODE_ATTACK_OFFSET, (void*) &CreativeMode$attack, (void**) &_CreativeMode$attack);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_ATTACK_OFFSET, (void*) &SurvivalMode$attack, (void**) &_SurvivalMode$attack);
	VirtualHook(CreativeMode$vtable, GAMEMODE_TICK_OFFSET, (void*) &CreativeMode$tick, (void**) &_CreativeMode$tick);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_TICK_OFFSET, (void*) &SurvivalMode$tick, (void**) &_SurvivalMode$tick);

	FLHookFunction(FLAddress(0x00000000 | 1, 0x100355e90), (void*) &LocalPlayer$LocalPlayer, (void**) &_LocalPlayer$LocalPlayer);
	FLHookFunction(FLAddress(0x00000000 | 1, 0x10008182c), (void*) &MinecraftClient$update, (void**) &_MinecraftClient$update);
	FLHookFunction(FLAddress(0x00000000 | 1, 0x10007ba50), (void*) &MinecraftClient$onResourcesLoaded, (void**) &_MinecraftClient$onResourcesLoaded);
}

void initInterpreter()
{
	interpreter = new CTinyJS();
	registerFunctions(interpreter);
	registerMathFunctions(interpreter);

	registerScriptCalls();
	initPointers();
}

MSInitialize // called when the process is loaded into MCPE
{
	initInterpreter();

	// Schedules scripts to load on the first MinecraftClient update
	SCRIPTS_NEED_INIT = true;
}
