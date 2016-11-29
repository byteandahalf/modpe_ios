#ifndef __MCPE_ITEM_H
#define __MCPE_ITEM_H

#include <string>
struct TextureUVCoordinateSet;

struct Item
{
	uintptr_t** vtable; // 0
	uint8_t maxStackSize; // 8
	int idk; // 12
	std::string atlas; // 16
	int frameCount; // 40
	bool animated; // 44
	short itemId; // 46
	std::string name; // 48
	std::string idk3; // 72
	bool isMirrored; // 96
	short maxDamage; // 98
	bool isGlint; // 100
	bool renderAsTool; // 101
	bool stackedByData; // 102
	uint8_t properties; // 103
	int maxUseDuration; // 104
	bool explodeable; // 108
	bool shouldDespawn; // 109
	bool idk4; // 110
	uint8_t useAnimation; // 111
	int creativeCategory; // 112
	float idk5; // 116
	float idk6; // 120
	TextureUVCoordinateSet& icon; // 124
	char filler[44]; // 132
};

/*
.data.rel.ro:01B75224         DCD _ZN4ItemD2Ev+1
.data.rel.ro:01B75228         DCD _ZN4ItemD0Ev+1
.data.rel.ro:01B7522C         DCD _ZN4Item7setIconERKSsi+1 ; Item::setIcon(std::string const&,int)
.data.rel.ro:01B75230         DCD _ZN4Item7setIconERK22TextureUVCoordinateSet+1 ; Item::setIcon(TextureUVCoordinateSet const&)
.data.rel.ro:01B75234         DCD _ZN4Item15setMaxStackSizeEh+1 ; Item::setMaxStackSize(uchar)
.data.rel.ro:01B75238         DCD _ZN4Item11setCategoryE20CreativeItemCategory+1 ; Item::setCategory(CreativeItemCategory)
.data.rel.ro:01B7523C         DCD _ZN4Item16setStackedByDataEb+1 ; Item::setStackedByData(bool)
.data.rel.ro:01B75240         DCD _ZN4Item12setMaxDamageEi+1 ; Item::setMaxDamage(int)
.data.rel.ro:01B75244         DCD _ZN4Item15setHandEquippedEv+1 ; Item::setHandEquipped(void)
.data.rel.ro:01B75248         DCD _ZN4Item15setUseAnimationE12UseAnimation+1 ; Item::setUseAnimation(UseAnimation)
.data.rel.ro:01B7524C         DCD _ZN4Item17setMaxUseDurationEi+1 ; Item::setMaxUseDuration(int)
.data.rel.ro:01B75250         DCD _ZN4Item23setRequiresWorldBuilderEb+1 ; Item::setRequiresWorldBuilder(bool)
.data.rel.ro:01B75254         DCD _ZN4Item13setExplodableEb+1 ; Item::setExplodable(bool)
.data.rel.ro:01B75258         DCD _ZN4Item10setIsGlintEb+1 ; Item::setIsGlint(bool)
.data.rel.ro:01B7525C         DCD _ZN4Item16setShouldDespawnEb+1 ; Item::setShouldDespawn(bool)
.data.rel.ro:01B75260         DCD _ZN4Item13canBeDepletedEv+1 ; Item::canBeDepleted(void)
.data.rel.ro:01B75264         DCD _ZNK4Item17canDestroySpecialEPK5Block+1 ; Item::canDestroySpecial(Block const*)
.data.rel.ro:01B75268         DCD _ZNK4Item23getLevelDataForAuxValueEi+1 ; Item::getLevelDataForAuxValue(int)
.data.rel.ro:01B7526C         DCD _ZNK4Item15isStackedByDataEv+1 ; Item::isStackedByData(void)
.data.rel.ro:01B75270         DCD _ZN4Item12getMaxDamageEv+1 ; Item::getMaxDamage(void)
.data.rel.ro:01B75274         DCD _ZN4Item15getAttackDamageEv+1 ; Item::getAttackDamage(void)
.data.rel.ro:01B75278         DCD _ZNK4Item14isHandEquippedEv+1 ; Item::isHandEquipped(void)
.data.rel.ro:01B7527C         DCD _ZNK4Item7isArmorEv+1 ; Item::isArmor(void)
.data.rel.ro:01B75280         DCD _ZNK4Item5isDyeEv+1 ; Item::isDye(void)
.data.rel.ro:01B75284         DCD _ZNK4Item7isGlintEPK12ItemInstance+1 ; Item::isGlint(ItemInstance const*)
.data.rel.ro:01B75288         DCD _ZNK4Item11isThrowableEv+1 ; Item::isThrowable(void)
.data.rel.ro:01B7528C         DCD _ZNK4Item20canDestroyInCreativeEv+1 ; Item::canDestroyInCreative(void)
.data.rel.ro:01B75290         DCD _ZNK4Item16isLiquidClipItemEi+1 ; Item::isLiquidClipItem(int)
.data.rel.ro:01B75294         DCD _ZNK4Item16requiresInteractEv+1 ; Item::requiresInteract(void)
.data.rel.ro:01B75298         DCD _ZNK4Item24appendFormattedHovertextERK12ItemInstanceR5LevelRSsb+1 ; Item::appendFormattedHovertext(ItemInstance const&,Level &,std::string &,bool)
.data.rel.ro:01B7529C         DCD _ZN4Item17isValidRepairItemERK12ItemInstanceS2_+1 ; Item::isValidRepairItem(ItemInstance const&,ItemInstance const&)
.data.rel.ro:01B752A0         DCD _ZNK4Item14getEnchantSlotEv+1 ; Item::getEnchantSlot(void)
.data.rel.ro:01B752A4         DCD _ZNK4Item15getEnchantValueEv+1 ; Item::getEnchantValue(void)
.data.rel.ro:01B752A8         DCD _ZNK4Item9isComplexEv+1 ; Item::isComplex(void)
.data.rel.ro:01B752AC         DCD _ZNK4Item15uniqueAuxValuesEv+1 ; Item::uniqueAuxValues(void)
.data.rel.ro:01B752B0         DCD _ZNK4Item8getColorERK12ItemInstance+1 ; Item::getColor(ItemInstance const&)
.data.rel.ro:01B752B4         DCD _ZN4Item3useER12ItemInstanceR6Player+1 ; Item::use(ItemInstance &,Player &)
.data.rel.ro:01B752B8         DCD _ZN4Item5useOnEP12ItemInstanceP6Playeriiiafff+1 ; Item::useOn(ItemInstance *,Player *,int,int,int,signed char,float,float,float)
.data.rel.ro:01B752BC         DCD _ZN4Item8dispenseER11BlockSourceR9ContaineriRK4Vec3a+1 ; Item::dispense(BlockSource &,Container &,int,Vec3 const&,signed char)
.data.rel.ro:01B752C0         DCD _ZN4Item15useTimeDepletedEP12ItemInstanceP5LevelP6Player+1 ; Item::useTimeDepleted(ItemInstance *,Level *,Player *)
.data.rel.ro:01B752C4         DCD _ZN4Item12releaseUsingEP12ItemInstanceP6Playeri+1 ; Item::releaseUsing(ItemInstance *,Player *,int)
.data.rel.ro:01B752C8         DCD _ZN4Item15getDestroySpeedEP12ItemInstanceP5Block+1 ; Item::getDestroySpeed(ItemInstance *,Block *)
.data.rel.ro:01B752CC         DCD _ZN4Item9hurtEnemyEP12ItemInstanceP3MobS3_+1 ; Item::hurtEnemy(ItemInstance *,Mob *,Mob *)
.data.rel.ro:01B752D0         DCD _ZN4Item13interactEnemyEP12ItemInstanceP3MobP6Player+1 ; Item::interactEnemy(ItemInstance *,Mob *,Player *)
.data.rel.ro:01B752D4         DCD _ZN4Item9mineBlockEP12ItemInstance7BlockIDiiiP3Mob+1 ; Item::mineBlock(ItemInstance *,BlockID,int,int,int,Mob *)
.data.rel.ro:01B752D8         DCD _ZNK4Item20buildDescriptionNameERK12ItemInstance+1 ; Item::buildDescriptionName(ItemInstance const&)
.data.rel.ro:01B752DC         DCD _ZNK4Item26buildEffectDescriptionNameERK12ItemInstance+1 ; Item::buildEffectDescriptionName(ItemInstance const&)
.data.rel.ro:01B752E0         DCD _ZNK4Item12readUserDataEP12ItemInstanceR10IDataInput+1 ; Item::readUserData(ItemInstance *,IDataInput &)
.data.rel.ro:01B752E4         DCD _ZNK4Item13writeUserDataEPK12ItemInstanceR11IDataOutput+1 ; Item::writeUserData(ItemInstance const*,IDataOutput &)
.data.rel.ro:01B752E8         DCD _ZN4Item15getMaxStackSizeEPK12ItemInstance+1 ; Item::getMaxStackSize(ItemInstance const*)
.data.rel.ro:01B752EC         DCD _ZN4Item13inventoryTickER12ItemInstanceR5LevelR6Entityib+1 ; Item::inventoryTick(ItemInstance &,Level &,Entity &,int,bool)
.data.rel.ro:01B752F0         DCD _ZN4Item11onCraftedByER12ItemInstanceR5LevelR6Player+1 ; Item::onCraftedBy(ItemInstance &,Level &,Player &)
.data.rel.ro:01B752F4         DCD _ZNK4Item15getInteractTextERK6Player+1 ; Item::getInteractText(Player const&)
.data.rel.ro:01B752F8         DCD _ZNK4Item20getAnimationFrameForER3Mob+1 ; Item::getAnimationFrameFor(Mob &)
.data.rel.ro:01B752FC         DCD _ZNK4Item10isEmissiveEi+1 ; Item::isEmissive(int)
.data.rel.ro:01B75300         DCD _ZNK4Item7getIconEiib+1 ; Item::getIcon(int,int,bool)
.data.rel.ro:01B75304         DCD _ZNK4Item14getIconYOffsetEv+1 ; Item::getIconYOffset(void)
.data.rel.ro:01B75308         DCD _ZNK4Item13isMirroredArtEv+1 ; Item::isMirroredArt(void)*/

#endif
