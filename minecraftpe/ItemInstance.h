#ifndef __MCPE_ITEMINSTANCE_H
#define __MCPE_ITEMINSTANCE_H

struct CompoundTag;
struct Item;
struct Block;

struct ItemInstance
{
	uint8_t count; // 0
	uint16_t aux; // 2
	CompoundTag* tag; // 4
	Item* item; // 12
	Block* block; // 20
	int idk[3]; // 28
}; // 40

#endif
