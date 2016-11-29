#ifndef __MODPESETITEMREQUEST_H
#define __MODPESETITEMREQUEST_H

#include <string>
#include <vector>
struct Item;

struct ModPESetItemRequest
{
	static std::vector<ModPESetItemRequest*> requests;
	static void clearRequests();
	static void request(ModPESetItemRequest*);
	virtual ~ModPESetItemRequest();

	virtual void fulfill() = 0;
};

struct ModPESetIconRequest : ModPESetItemRequest
{
	Item* itemPtr;
	std::string icon_name;
	int icon_index;

	ModPESetIconRequest(Item*, std::string, int);

	virtual void fulfill();
};

#endif