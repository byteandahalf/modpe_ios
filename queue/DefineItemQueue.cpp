#include "DefineItemQueue.h"
#include "../externs.h"

#include "../minecraftpe/Item.h"

#include <cstdlib>

std::map<int, DefineItemTask*> DefineItemQueue::queue;

void DefineItemQueue::QueueOrImmediateItemCreation(int itemId, const std::string& icon_name, int icon_index, const std::string& name, uint8_t maxStackSize)
{
	if(queue.empty())
	{
		// I have no idea why I need to clear this; it segfaults otherwise. Likely a compiler/STL bug
		queue.clear();
	}
	if(queue.find(itemId) != queue.end())
	{
		// This item task has already been requested
		return;
	}

	DefineItemTask* task = new DefineItemTask(itemId, icon_name, icon_index, name, maxStackSize);
	if(ITEMS_CREATED)
	{
		// If items are already defined, immediately do this task rather than queue it
		task->doTask();
		delete task;
	}
	else
	{
		queue.insert({itemId, task});
	}
}

void DefineItemQueue::doTasks()
{
	typedef std::map<int, DefineItemTask*>::iterator it_type;
	for(it_type iterator = queue.begin(); iterator != queue.end(); iterator++)
	{
		if(iterator->second != NULL)
		{
    		iterator->second->doTask();
    		delete iterator->second;
		}
    	queue.erase(iterator->first);
	}
	queue.clear();
}


DefineItemTask::DefineItemTask(int itemId, const std::string& icon_name, int icon_index, const std::string& name, uint8_t maxStackSize)
:	itemId(itemId),
	icon_name(icon_name),
	icon_index(icon_index),
	name(name),
	maxStackSize(maxStackSize)
{}

void DefineItemTask::doTask()
{
	Item* myItemPtr = (Item*) malloc(sizeof(Item));
	Item$Item(myItemPtr, name, itemId - 0x100);
	myItemPtr->maxStackSize = maxStackSize;
	void (*setIcon)(Item*, const std::string&, int) = (void (*)(Item*, const std::string&, int))((uintptr_t***) myItemPtr)[0][2];
	setIcon(myItemPtr, icon_name, icon_index);

	Item$mItems[itemId] = myItemPtr;
}
