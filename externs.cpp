#include <cstdint>
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

//the JavaScript interpreter
CTinyJS* interpreter;

//various helpers
bool PREVENTDEFAULT = false;

//pointers
LocalPlayer* MCPE_localplayer;
MinecraftClient* MCPE_client;
uintptr_t** CreativeMode$vtable;
uintptr_t** SurvivalMode$vtable;

//function pointers
void (*Level$explode)(Level*, BlockSource*, Entity*, const Vec3&, float, bool, bool, float);
bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
FullBlock (*BlockSource$getBlockAndData)(BlockSource*, const BlockPos&);
uint64_t& (*Entity$getUniqueID)(Entity*);
Entity* (*Level$fetchEntity)(Level*, uint64_t, bool);
void (*GuiData$addMessage)(GuiData*, const std::string&, const std::string&, int, bool);
