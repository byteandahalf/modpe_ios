#include <sys/stat.h>
#include <cstdio>
#include <iostream>

#include <Forklift/Forklift.h>

#include "TinyJS.h"

//constants
#define GAMEMODE_USEITEMON_OFFSET 13

//forward decs for prototypes
struct BlockSource;
struct ItemInstance;
struct BlockPos;
struct FullBlock;

#include "externs.h" // for function pointers

//callback prototypes
extern bool (*_CreativeMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
bool CreativeMode$useItemOn(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
extern bool (*_SurvivalMode$useItemOn)(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
bool SurvivalMode$useItemOn(uintptr_t*, uintptr_t*, ItemInstance&, const BlockPos&, signed char, uintptr_t*);
extern BlockSource* (*_BlockSource$BlockSource)(BlockSource*, uintptr_t*, uintptr_t*, uintptr_t*, bool, bool);
BlockSource* BlockSource$BlockSource(BlockSource*, uintptr_t*, uintptr_t*, uintptr_t*, bool, bool);
/*
*	ModPE calls
*/
//top-level
void print(CScriptVar*, void*);
void setTile(CScriptVar*, void*);
void preventDefault(CScriptVar*, void*);


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
	interpreter->addNative("function setTile(x, y, z, blockId, data)", setTile, interpreter);
	interpreter->addNative("function preventDefault()", preventDefault, interpreter);
}

void VirtualHook(uintptr_t** vtable, short offset, void* hook, void** real);

void initPointers()
{
	// currently only arm64 support
	FLHookSymbol(BlockSource$setBlockAndData, 0x1005CE8FC);

	FLHookSymbol(CreativeMode$vtable, 0x100EEA030);
	FLHookSymbol(SurvivalMode$vtable, 0x100E72E10);
	VirtualHook(CreativeMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &CreativeMode$useItemOn, (void**) &_CreativeMode$useItemOn);
	VirtualHook(SurvivalMode$vtable, GAMEMODE_USEITEMON_OFFSET, (void*) &SurvivalMode$useItemOn, (void**) &_SurvivalMode$useItemOn);

	FLHookFunction(0x1005CC208, (void*) &BlockSource$BlockSource, (void**) &_BlockSource$BlockSource);
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
