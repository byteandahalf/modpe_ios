#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"
#include "../minecraftpe/ItemInstance.h"

#include <string>

uint64_t strToU64(const std::string&);
ItemInstance* newItemInstance(int, uint8_t, uint16_t);


Entity* modpe_entityWrapper(uint64_t uniqueID)
{
	Entity* retval = Level$fetchEntity(MCPE_localplayer->level, uniqueID, false);

	if(!retval)
		retval = MCPE_localplayer;

	return retval;
}

bool canAddRider_hack()
{
	return true;
}

namespace EntityNS
{
void getEntityTypeId(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));
	int (*getEntityTypeId)(Entity*) = (int (*)(Entity*))((uintptr_t***) entity)[0][97];

	jsfunc->setReturnVar(new CScriptVar(getEntityTypeId(entity)));
}
void remove(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	void (*remove)(Entity*) = (void (*)(Entity*))((uintptr_t***) entity)[0][8];
	remove(entity);
}
void getVelX(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	// use vtable pointers since they aren't guaranteed to change across updates
	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[13];

	jsfunc->setReturnVar(new CScriptVar(getVelocity(entity).x));
}
void getVelY(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[13];

	jsfunc->setReturnVar(new CScriptVar(getVelocity(entity).y));
}
void getVelZ(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[13];

	jsfunc->setReturnVar(new CScriptVar(getVelocity(entity).z));
}
void setVelX(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[13];
	void (*lerpMotion)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[21];

	float velX = static_cast<float>(jsfunc->getParameter("velocity")->getDouble());
	float velY = getVelocity(entity).y;
	float velZ = getVelocity(entity).z;

	lerpMotion(entity, Vec3{velX, velY, velZ});
}
void setVelY(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[13];
	void (*lerpMotion)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[21];

	float velX = getVelocity(entity).x;
	float velY = static_cast<float>(jsfunc->getParameter("velocity")->getDouble());
	float velZ = getVelocity(entity).z;

	lerpMotion(entity, Vec3{velX, velY, velZ});
}
void setVelZ(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[13];
	void (*lerpMotion)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[21];

	float velX = getVelocity(entity).x;
	float velY = getVelocity(entity).y;
	float velZ = static_cast<float>(jsfunc->getParameter("velocity")->getDouble());

	lerpMotion(entity, Vec3{velX, velY, velZ});
}

void getPosX(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	jsfunc->setReturnVar(new CScriptVar(getPos(entity).x));
}
void getPosY(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	jsfunc->setReturnVar(new CScriptVar(getPos(entity).y));
}
void getPosZ(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	jsfunc->setReturnVar(new CScriptVar(getPos(entity).z));
}
void setPosition(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	void (*setPos)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[9];

	float x = 	static_cast<float>(jsfunc->getParameter("x")->getDouble()),
		y = 	static_cast<float>(jsfunc->getParameter("y")->getDouble()),
		z = 	static_cast<float>(jsfunc->getParameter("z")->getDouble());

	setPos(entity, Vec3{x, y, z});
}
void setPositionRelative(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));

	uintptr_t** vtable = *((uintptr_t***) entity);
	void (*setPos)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[9];
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	float x = 	static_cast<float>(jsfunc->getParameter("x")->getDouble()) + getPos(entity).x,
		y = 	static_cast<float>(jsfunc->getParameter("y")->getDouble()) + getPos(entity).y, 
		z = 	static_cast<float>(jsfunc->getParameter("z")->getDouble()) + getPos(entity).z;

	setPos(entity, Vec3{x, y, z});
}
void setFireTicks(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));
	int ticks = jsfunc->getParameter("ticks")->getInt();

	void (*setOnFire)(Entity*, int) = (void (*)(Entity*, int))((uintptr_t***) entity)[0][101];
	setOnFire(entity, ticks);
}
void rideAnimal(CScriptVar* jsfunc, void*)
{
	Entity* rider = modpe_entityWrapper(strToU64(jsfunc->getParameter("rider")->getString()));
	Entity* ride = modpe_entityWrapper(strToU64(jsfunc->getParameter("ride")->getString()));

	void (*stopRiding)(Entity*, bool, bool) = (void (*)(Entity*, bool, bool))((uintptr_t***) rider)[0][120];
	void (*startRiding)(Entity*, Entity*) = (void (*)(Entity*, Entity*))((uintptr_t***) rider)[0][26];
	uintptr_t** rideVtable = ((uintptr_t***) ride)[0];
	bool (*canAddRider_orig)(Entity*, Entity*) = (bool (*)(Entity*, Entity*)) rideVtable[114];

	if(!canAddRider_orig(ride, rider))
	{
		// If this Entity cannot be ridden, then YES IT CAN BECAUSE I SAID SO
		rideVtable[114] = (uintptr_t*) &canAddRider_hack;
		startRiding(rider, ride);
		rideVtable[114] = (uintptr_t*) canAddRider_orig;
	}
	else
	{
		startRiding(rider, ride);
	}
}
void setCarriedItem(CScriptVar* jsfunc, void*)
{
	int itemId = jsfunc->getParameter("itemId")->getInt(),
		count = jsfunc->getParameter("count")->getInt(),
		aux = jsfunc->getParameter("aux")->getInt();

	Entity* entity = modpe_entityWrapper(strToU64(jsfunc->getParameter("uniqueID")->getString()));
	ItemInstance* (*getCarriedItem)(Entity*) = (ItemInstance* (*)(Entity*))((uintptr_t***) entity)[0][184];

	ItemInstance* ptr_to_carried = getCarriedItem(entity);
	if(ptr_to_carried == NULL)
	{
		// Not Player or HumanoidMonster
		return;
	}

	ItemInstance* new_carried = newItemInstance(itemId, count, aux);

	ItemInstance$operator_equals(ptr_to_carried, *new_carried);
	delete new_carried;
}
};
