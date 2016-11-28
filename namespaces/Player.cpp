#include "../TinyJS.h"

#include "../externs.h"
#include "../minecraftpe/Player.h"

namespace PlayerNS
{
void getEntity(CScriptVar* jsfunc, void*)
{
	// TODO: this doesn't work since CScriptVar doesn't have a uint64_t constructor
	jsfunc->setReturnVar(new CScriptVar((long) Entity$getUniqueID(MCPE_localplayer)));
}
};
