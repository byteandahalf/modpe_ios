#ifndef __MCPE_LOCALPLAYER_H
#define __MCPE_LOCALPLAYER_H

#include "Entity.h"
struct PlayerInventoryProxy;

struct Player
:public Entity
{
	char filler[4400]; // 184
	PlayerInventoryProxy* inventory; // 4584
};

struct LocalPlayer
:public Player
{};

#endif
