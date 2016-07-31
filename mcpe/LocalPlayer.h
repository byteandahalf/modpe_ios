#ifndef __MCPE_LOCALPLAYER_H
#define __MCPE_LOCALPLAYER_H

struct BlockSource;

struct LocalPlayer
{
	char filler[496];
	BlockSource* region;
};

#endif
