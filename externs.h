#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <stdint.h>

struct CTinyJS;
struct BlockSource;
struct LocalPlayer;
struct FullBlock;
struct BlockPos;
struct Entity;

extern CTinyJS* interpreter;

extern bool PREVENTDEFAULT;

extern LocalPlayer* MCPE_localplayer;
extern uintptr_t** CreativeMode$vtable;
extern uintptr_t** SurvivalMode$vtable;

extern bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
extern FullBlock (*BlockSource$getBlockAndData)(BlockSource*, const BlockPos&);
extern uint64_t (*Entity$getUniqueID)(Entity*);

#endif