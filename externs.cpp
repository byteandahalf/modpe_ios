struct CTinyJS;
struct BlockSource;
struct LocalPlayer;
struct FullBlock;

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
