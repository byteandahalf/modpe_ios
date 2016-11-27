#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <stdint.h>
#include <string>

struct CTinyJS;
struct BlockSource;
struct LocalPlayer;
struct MinecraftClient;
struct FullBlock;
struct BlockPos;
struct Entity;
struct Level;
struct GuiData;
struct Vec3;

extern CTinyJS* interpreter;

extern bool PREVENTDEFAULT;

extern LocalPlayer* MCPE_localplayer;
extern MinecraftClient* MCPE_client;
extern uintptr_t** CreativeMode$vtable;
extern uintptr_t** SurvivalMode$vtable;

extern void (*Level$explode)(Level*, BlockSource*, Entity*, const Vec3&, float, bool, bool, float);
extern bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
extern FullBlock (*BlockSource$getBlockAndData)(BlockSource*, const BlockPos&);
extern uint64_t (*Entity$getUniqueID)(Entity*);
extern Entity* (*Level$getEntity)(Level*, uint64_t, bool);
extern void (*GuiData$addMessage)(GuiData*, const std::string&, const std::string&, int, bool);

#endif