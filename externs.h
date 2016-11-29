#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <cstdint>
#include <string>
#include <memory>

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
struct PlayerInventoryProxy;
struct Item;
struct ItemInstance;
struct InventorySlot;
struct TextureAtlas;

extern CTinyJS* interpreter;

extern bool PREVENTDEFAULT;

extern LocalPlayer* MCPE_localplayer;
extern MinecraftClient* MCPE_client;
extern uintptr_t** CreativeMode$vtable;
extern uintptr_t** SurvivalMode$vtable;
extern Item** Item$mItems;
extern std::shared_ptr<TextureAtlas>* Item$mTextureAtlas;

extern void (*Level$explode)(Level*, BlockSource*, Entity*, const Vec3&, float, bool, bool, float);
extern bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
extern FullBlock (*BlockSource$getBlockAndData)(BlockSource*, const BlockPos&);
extern uint64_t& (*Entity$getUniqueID)(Entity*);
extern Entity* (*Level$fetchEntity)(Level*, uint64_t, bool);
extern void (*GuiData$addMessage)(GuiData*, const std::string&, const std::string&, int, bool);
extern InventorySlot (*PlayerInventoryProxy$getSelectedSlot)(PlayerInventoryProxy*);
extern const ItemInstance& (*PlayerInventoryProxy$getItem)(PlayerInventoryProxy*, int, int);
extern void (*PlayerInventoryProxy$clearSlot)(PlayerInventoryProxy*, int, int);
extern Item* (*Item$Item)(Item*, const std::string&, short);

#endif