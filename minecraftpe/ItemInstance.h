#ifndef __MCPE_ITEMINSTANCE_H
#define __MCPE_ITEMINSTANCE_H

struct CompoundTag;
struct Item;
struct Block;

struct ItemInstance
{
	uint8_t count;
	uint16_t aux;
	CompoundTag* tag;
	Item* item;
	Block* block;
	int idk;
};

#endif
