#ifndef __MCPE_ENTITY_H
#define __MCPE_ENTITY_H

struct Level;
struct BlockSource;

struct Entity
{
	char filler[64];
	Level* level; // 64
	char filler2[104]; // 72
	BlockSource* region; // 176
};

#endif
