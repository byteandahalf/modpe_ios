#ifndef __MODPEQUEUE_H
#define __MODPEQUEUE_H

#include <map>
#include <string>

struct DefineItemTask;

struct DefineItemQueue
{
	static std::map<int, DefineItemTask*> queue;
	static void QueueOrImmediateItemCreation(int, const std::string&, int, const std::string&, uint8_t);
	static void doTasks();
};

struct DefineItemTask
{
	int itemId;
	std::string icon_name;
	int icon_index;
	std::string name;
	uint8_t maxStackSize;

	DefineItemTask(int, const std::string&, int, const std::string&, uint8_t);

	virtual void doTask();
};

#endif