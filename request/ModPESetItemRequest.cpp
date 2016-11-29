#include "ModPESetItemRequest.h"

#include "../externs.h"
#include "../minecraftpe/Item.h"

std::vector<ModPESetItemRequest*> ModPESetItemRequest::requests;

ModPESetItemRequest::~ModPESetItemRequest()
{}

void ModPESetItemRequest::clearRequests()
{
	for(ModPESetItemRequest* request : requests)
	{
		delete request;
	}
	requests.clear();
}

void ModPESetItemRequest::request(ModPESetItemRequest* request)
{
	requests.push_back(request);
}


ModPESetIconRequest::ModPESetIconRequest(Item* itemPtr, std::string icon_name, int icon_index)
:	itemPtr(itemPtr),
	icon_name(icon_name),
	icon_index(icon_index)
{}

void ModPESetIconRequest::fulfill()
{
	if(!(*Item$mTextureAtlas) || !itemPtr)
	{
		return;
	}
	// Set Item icon via its vtable
	void (*setIcon)(Item*, const std::string&, int) = (void (*)(Item*, const std::string&, int))((uintptr_t***) itemPtr)[0][2];
	setIcon(itemPtr, icon_name, icon_index);
}
