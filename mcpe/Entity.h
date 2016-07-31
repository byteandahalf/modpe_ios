#ifndef __MCPE_ENTITY_H
#define __MCPE_ENTITY_H

struct BlockSource;

struct Entity
{
	char filler[144];
	Level* level; // 144
	char filler2[344]; // 152
	BlockSource* region; // 496
};

#endif
