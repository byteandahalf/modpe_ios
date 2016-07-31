#include <sys/stat.h>
#include <cstdio>
#include <iostream>

#include <Forklift/Forklift.h>

#include "TinyJS.h"

//constants
#define GAMEMODE_USEITEMON_OFFSET 13
#define GAMEMODE_ATTACK_OFFSET 15

//forward decs for prototypes
struct LocalPlayer;
struct ItemInstance;
struct BlockPos;
struct FullBlock;
struct Player;
struct Entity;

#include "externs.h" // for function pointers

//callback prototypes
extern bool (*_CreativeMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
bool CreativeMode$useItemOn(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
extern bool (*_SurvivalMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
bool SurvivalMode$useItemOn(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
extern void (*_GameMode$attack)(uintptr_t*, Player*, Entity*);
void GameMode$attack(uintptr_t*, Player*, Entity*);
extern LocalPlayer* (*_LocalPlayer$LocalPlayer)(LocalPlayer*, uintptr_t*, uintptr_t*, uintptr_t*, int, uintptr_t*, uintptr_t*);
LocalPlayer* LocalPlayer$LocalPlayer(LocalPlayer*, uintptr_t*, uintptr_t*, uintptr_t*, int, uintptr_t*, uintptr_t*);
/*
*	ModPE calls
*/
//top-level
void print(CScriptVar*, void*);
void preventDefault(CScriptVar*, void*);
//Level
namespace Level
{
	void setTile(CScriptVar*, void*);
	void getTile(CScriptVar*, void*);
	void getData(CScriptVar*, void*);
};


void runTestScript()
{
	const char* script = "var/mobile/Media/script.js";

	struct stat results;
	if(!stat(script, &results) == 0)
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
	interpreter->addNative("function preventDefault()", preventDefault, interpreter);

	interpreter->addNative("function Level.setTile(x, y, z, blockId, data)", Level::setTile, interpreter);
	interpreter->addNative("function Level.getTile(x, y, z)", Level::getTile, interpreter);
	interpreter->addNative("function Level.getData(x, y, z)", Level::getData, interpreter);
}

void VirtualHook(uintptr_t** vtable, short offset, void* hook, void** real);

void initPointers()
{
	// currently only arm64 support
	FLHookSymbol(BlockSource$setBlockAndData, 0x1005CE8FC);
	FLHookSymbol(BlockSource$getBlockAndData, 0x1005CD0C0);
	FLHookSymbol(Entity$getUniqueID, 0x1004D347C);

	FLHookSymbol(CreativeMode$vtable, 0x100EEA030);
	FLHookSymbol(SurvivalMode$vtable, 0x100E72E10);
	VirtualHook(CreativeMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &CreativeMode$useItemOn, (void**) &_CreativeMode$useItemOn);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &SurvivalMode$useItemOn, (void**) &_SurvivalMode$useItemOn);
	VirtualHook(CreativeMode$vtable, GAMEMODE_ATTACK_OFFSET, (void*) &GameMode$attack, (void**) &_GameMode$attack);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_ATTACK_OFFSET, (void*) &GameMode$attack, (void**) &_GameMode$attack);

	FLHookFunction(0x1002C47E8, (void*) &LocalPlayer$LocalPlayer, (void**) &_LocalPlayer$LocalPlayer);
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
