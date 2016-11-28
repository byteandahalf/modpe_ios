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
};
namespace EntityNS
{
	void getVelX(CScriptVar*, void*);
	void getVelY(CScriptVar*, void*);
	void getVelZ(CScriptVar*, void*);
	void getPosX(CScriptVar*, void*);
	void getPosY(CScriptVar*, void*);
	void getPosZ(CScriptVar*, void*);
	void setPosition(CScriptVar*, void*);
	void setPositionRelative(CScriptVar*, void*);
};
namespace PlayerNS
{
	void getEntity(CScriptVar*, void*);
	void clearInventorySlot(CScriptVar*, void*);
	void getSelectedSlotId(CScriptVar*, void*);
	void getCarriedItem(CScriptVar*, void*);
	void getCarriedItemCount(CScriptVar*, void*);
	void getCarriedItemData(CScriptVar*, void*);
	void getInventorySlot(CScriptVar*, void*);
	void getInventorySlotCount(CScriptVar*, void*);
	void getInventorySlotData(CScriptVar*, void*);
};


void runTestScript()
{
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

	interpreter->addNative("function Entity.getPosX(uniqueID)", EntityNS::getPosX, interpreter);
	interpreter->addNative("function Entity.getPosY(uniqueID)", EntityNS::getPosY, interpreter);
	interpreter->addNative("function Entity.getPosZ(uniqueID)", EntityNS::getPosZ, interpreter);
	interpreter->addNative("function Entity.setPosition(uniqueID, x, y, z)", EntityNS::setPosition, interpreter);
	interpreter->addNative("function Entity.setPositionRelative(uniqueID, x, y, z)", EntityNS::setPositionRelative, interpreter);
	interpreter->addNative("function Entity.getVelX(uniqueID)", EntityNS::getVelX, interpreter);
	interpreter->addNative("function Entity.getVelY(uniqueID)", EntityNS::getVelY, interpreter);
	interpreter->addNative("function Entity.getVelZ(uniqueID)", EntityNS::getVelZ, interpreter);

	interpreter->addNative("function Player.getEntity()", PlayerNS::getEntity, interpreter);
	interpreter->addNative("function Player.clearInventorySlot(slotId)", PlayerNS::clearInventorySlot, interpreter);
	interpreter->addNative("function Player.getSelectedSlotId()", PlayerNS::getSelectedSlotId, interpreter);
	interpreter->addNative("function Player.getCarriedItem()", PlayerNS::getCarriedItem, interpreter);
	interpreter->addNative("function Player.getCarriedItemCount()", PlayerNS::getCarriedItemCount, interpreter);
	interpreter->addNative("function Player.getCarriedItemData()", PlayerNS::getCarriedItemData, interpreter);
	interpreter->addNative("function Player.getInventorySlot(slotId)", PlayerNS::getInventorySlot, interpreter);
	interpreter->addNative("function Player.getInventorySlotCount(slotId)", PlayerNS::getInventorySlotCount, interpreter);
	interpreter->addNative("function Player.getInventorySlotData(slotId)", PlayerNS::getInventorySlotData, interpreter);
}


void VirtualHook(uintptr_t** vtable, short offset, void* hook, void** real);

void initPointers()
{
	// currently only arm64 support
	FLHookSymbol(Level$explode, FLAddress(0x00000000 | 1, 0x1007a9118));
	FLHookSymbol(BlockSource$setBlockAndData, FLAddress(0x00000000 | 1, 0x10079bc80));
	FLHookSymbol(BlockSource$getBlockAndData, FLAddress(0x00000000 | 1, 0x10079a1fc));
	FLHookSymbol(Entity$getUniqueID, FLAddress(0x00000000 | 1, 0x100657960));
	FLHookSymbol(Level$fetchEntity, FLAddress(0x00000000 | 1, 0x1007a8920));
	FLHookSymbol(GuiData$addMessage, FLAddress(0x00000000 | 1, 0x100108428));
	FLHookSymbol(PlayerInventoryProxy$getSelectedSlot, FLAddress(0x00000000 | 1, 0x1007168c8));
	FLHookSymbol(PlayerInventoryProxy$getItem, FLAddress(0x00000000 | 1, 0x100716884));
	FLHookSymbol(PlayerInventoryProxy$clearSlot, FLAddress(0x00000000 | 1, 0x10071665c));
	//0x1007a76f0 playSound

	FLHookSymbol(CreativeMode$vtable, FLAddress(0x00000000, 0x1011D7C78));
	FLHookSymbol(SurvivalMode$vtable, FLAddress(0x00000000, 0x10113DDC0));
	VirtualHook(CreativeMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &CreativeMode$useItemOn, (void**) &_CreativeMode$useItemOn);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &SurvivalMode$useItemOn, (void**) &_SurvivalMode$useItemOn);
	VirtualHook(CreativeMode$vtable, GAMEMODE_ATTACK_OFFSET, (void*) &CreativeMode$attack, (void**) &_CreativeMode$attack);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_ATTACK_OFFSET, (void*) &SurvivalMode$attack, (void**) &_SurvivalMode$attack);
	VirtualHook(CreativeMode$vtable, GAMEMODE_TICK_OFFSET, (void*) &CreativeMode$tick, (void**) &_CreativeMode$tick);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_TICK_OFFSET, (void*) &SurvivalMode$tick, (void**) &_SurvivalMode$tick);

	FLHookFunction(FLAddress(0x00000000 | 1, 0x100355e90), (void*) &LocalPlayer$LocalPlayer, (void**) &_LocalPlayer$LocalPlayer);
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

	runTestScript();
}
