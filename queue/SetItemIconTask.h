#ifndef __SETITEMICONTASK_H
#define __SETITEMICONTASK_H

#include "ModPEQueue.h"

#include <string>

struct SetItemIconTask: ModPETask
{
	int itemId;
	std::string icon_name;
	int icon_index;

	SetItemIconTask(int, const std::string&, int);

	virtual void doTask() const;
};

#endif