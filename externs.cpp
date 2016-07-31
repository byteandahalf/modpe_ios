#include <stdint.h>

struct CTinyJS;
struct BlockSource;
struct LocalPlayer;
struct FullBlock;
struct BlockPos;
struct Entity;
struct Level;

//the JavaScript interpreter
CTinyJS* interpreter;

//various helpers
bool PREVENTDEFAULT = false;

//pointers
LocalPlayer* MCPE_localplayer;
uintptr_t** CreativeMode$vtable;
uintptr_t** SurvivalMode$vtable;

//function pointers
bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
FullBlock (*BlockSource$getBlockAndData)(BlockSource*, const BlockPos&);
uint64_t (*Entity$getUniqueID)(Entity*);
Entity* (*Level$getEntity)(Level*, uint64_t, bool);
