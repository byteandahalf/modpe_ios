#ifndef __MCPE_LEVEL_H
#define __MCPE_LEVEL_H

struct LevelData
{
	char filler[48]; // 0
	std::string levelName; // 48
	char filler2[44]; // 72
	int time; // 116
	char filler3[144]; // 120
	int gameType; // 264
	int difficulty; // 268
};

struct Level
{
	char filler[160]; // 0
	LevelData data; // 160
};

#endif
