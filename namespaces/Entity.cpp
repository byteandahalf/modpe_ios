#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"

#include <string>

uint64_t strToU64(const std::string&);


Entity* modpe_entityWrapper(uint64_t uniqueID)
{
	Entity* retval = Level$fetchEntity(MCPE_localplayer->level, uniqueID, false);

	if(!retval)
		retval = MCPE_localplayer;

	return retval;
}


namespace EntityNS
{
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
};
