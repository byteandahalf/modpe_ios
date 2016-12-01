#include "SetItemIconTask.h"

#include "../externs.h"

#include "../minecraftpe/Item.h"

SetItemIconTask::SetItemIconTask(int itemId, const std::string& icon_name, int icon_index)
:	ModPETask(TaskType::TASK_SETICON),

	itemId(itemId),
	icon_name(icon_name),
	icon_index(icon_index)
{}

void SetItemIconTask::doTask() const
{
	Item* itemPtr = Item$mItems[itemId];

	if(itemPtr != NULL)
	{
		void (*setIcon)(Item*, const std::string&, int) = (void (*)(Item*, const std::string&, int))((uintptr_t***) itemPtr)[0][2];
		setIcon(itemPtr, icon_name, icon_index);
	}
}
