#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/common.h"
#include "../minecraftpe/Player.h"

Entity* modpe_entityWrapper(uint64_t uniqueID)
{
	return Level$getEntity(MCPE_localplayer->level, uniqueID, false);
}

namespace EntityNS
{
void getVelX(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	// use vtable pointers since they aren't guaranteed to change across updates
	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	jsfunc->setReturnVar(new CScriptVar((double) getVelocity(entity).x));
}
void getVelY(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	jsfunc->setReturnVar(new CScriptVar((double) getVelocity(entity).y));
}
void getVelZ(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getVelocity)(Entity*) = (const Vec3& (*)(Entity*)) vtable[10];

	jsfunc->setReturnVar(new CScriptVar((double) getVelocity(entity).z));
}

void getPosX(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[7];

	jsfunc->setReturnVar(new CScriptVar((double) getPos(entity).x));
}
void getPosY(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[7];

	jsfunc->setReturnVar(new CScriptVar((double) getPos(entity).y));
}
void getPosZ(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[7];

	jsfunc->setReturnVar(new CScriptVar((double) getPos(entity).z));
}

void setPosition(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	void (*setPos)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[6];

	float x = jsfunc->getParameter("x")->getDouble(),
		y = jsfunc->getParameter("y")->getDouble(),
		z = jsfunc->getParameter("z")->getDouble();

	setPos(entity, Vec3{x, y, z});
}
void setPositionRelative(CScriptVar* jsfunc, void*)
{
	Entity* entity = modpe_entityWrapper(jsfunc->getParameter("uniqueID")->getInt());

	uintptr_t** vtable = *((uintptr_t***) entity);
	void (*setPos)(Entity*, const Vec3&) = (void (*)(Entity*, const Vec3&)) vtable[6];
	const Vec3& (*getPos)(Entity*) = (const Vec3& (*)(Entity*)) vtable[7];

	float x = jsfunc->getParameter("x")->getDouble() + getPos(entity).x,
		y = jsfunc->getParameter("y")->getDouble() + getPos(entity).y,
		z = jsfunc->getParameter("z")->getDouble() + getPos(entity).z;

	setPos(entity, Vec3{x, y, z});
}
};
