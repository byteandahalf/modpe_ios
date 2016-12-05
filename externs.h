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
struct BlockEntity;

extern CTinyJS* interpreter;

extern bool PREVENTDEFAULT;
extern bool GRAPHICS_LOADED;
extern bool SCRIPTS_NEED_INIT;

extern LocalPlayer* MCPE_localplayer;
extern MinecraftClient* MCPE_client;
extern uintptr_t** CreativeMode$vtable;
extern uintptr_t** SurvivalMode$vtable;
extern Item** Item$mItems;

extern void (*Level$explode)(Level*, BlockSource*, Entity*, const Vec3&, float, bool, bool, float);
extern bool (*BlockSource$setBlockAndData)(BlockSource*, int, int, int, FullBlock, int);
extern FullBlock (*BlockSource$getBlockAndData)(BlockSource*, const BlockPos&);
extern BlockEntity* (*BlockSource$getBlockEntity)(BlockSource*, const BlockPos&);
extern uint64_t& (*Entity$getUniqueID)(Entity*);
extern Entity* (*Level$fetchEntity)(Level*, uint64_t, bool);
extern void (*GuiData$addMessage)(GuiData*, const std::string&, const std::string&, int, bool);
extern InventorySlot (*PlayerInventoryProxy$getSelectedSlot)(PlayerInventoryProxy*);
extern const ItemInstance& (*PlayerInventoryProxy$getItem)(PlayerInventoryProxy*, int, int);
extern void (*PlayerInventoryProxy$add)(PlayerInventoryProxy*, ItemInstance&, bool);
extern int (*PlayerInventoryProxy$getLinkedSlotsCount)(PlayerInventoryProxy*);
extern int (*PlayerInventoryProxy$getLinkedSlot)(PlayerInventoryProxy*, int);
extern void (*PlayerInventoryProxy$replaceSlot)(PlayerInventoryProxy*, int, const ItemInstance&);
extern void (*PlayerInventoryProxy$clearSlot)(PlayerInventoryProxy*, int, int);
extern Item* (*Item$Item)(Item*, const std::string&, short);
extern ItemInstance* (*ItemInstance$fromItem)(ItemInstance*, Item*);
extern void (*ItemInstance$operator_equals)(ItemInstance*, const ItemInstance&);
extern const std::string& (*SignBlockEntity$getMessage)(BlockEntity*, int);
extern void (*SignBlockEntity$setMessage)(BlockEntity*, const std::string&, int);
extern int& (*BlockEntity$getType)(BlockEntity*);
extern void (*MinecraftClient$play)(MinecraftClient*, const std::string&, const Vec3&, float, float);
extern void (*Level$addParticle)(Level*, int, const Vec3&, const Vec3&, int);
extern int (*ParticleTypeFromString)(const std::string&);

#endif