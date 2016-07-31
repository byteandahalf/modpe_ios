#ifndef __MCPE_ENTITY_H
#define __MCPE_ENTITY_H

struct BlockSource;

struct Entity
{
	char filler[496];
	BlockSource* region;
};

#endif
