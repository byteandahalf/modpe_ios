struct CTinyJS;
struct BlockSource;
struct FullBlock;

//the JavaScript interpreter
CTinyJS* interpreter;

//various helpers
bool PREVENTDEFAULT = false;

//pointers
BlockSource* MCPE_region;
uintptr_t** CreativeMode$vtable;
uintptr_t** SurvivalMode$vtable;

//function pointers
bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
