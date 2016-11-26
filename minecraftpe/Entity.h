#ifndef __MCPE_ENTITY_H
#define __MCPE_ENTITY_H

struct Level;
struct BlockSource;

struct Entity
{
	char filler[48];
	Level* level; // 48
	char filler2[440]; // 56
	BlockSource* region; // 496
};

#endif
