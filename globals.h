#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "TinyJS.h"

struct BlockSource;
struct FullBlock;

extern CTinyJS* interpreter;

extern bool PREVENTDEFAULT;

extern BlockSource* MCPE_region;
extern uintptr_t** CreativeMode$vtable;
extern uintptr_t** SurvivalMode$vtable;

extern bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);

#endif