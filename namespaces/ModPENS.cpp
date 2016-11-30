#include "../TinyJS.h"

#include "../externs.h"
#include "../queue/DefineItemQueue.h"

#include <string>

namespace ModPENS
{
void setItem(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt();
	std::string icon_name = jsfunc->getParameter("icon_name")->getString();
	int icon_index = jsfunc->getParameter("icon_index")->getInt();
	std::string name = jsfunc->getParameter("name")->getString();
	int stackSize = jsfunc->getParameter("stackSize")->getInt();

	DefineItemQueue::QueueOrImmediateItemCreation(itemId, icon_name, icon_index, name, stackSize);
}
};
