#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/Player.h"

#include <string>

std::string tostr64(uint64_t);


namespace PlayerNS
{
void getEntity(CScriptVar* jsfunc, void*)
{
	jsfunc->setReturnVar(new CScriptVar(tostr64(Entity$getUniqueID(MCPE_localplayer))));
}
};
