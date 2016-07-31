#include "../TinyJS.h"

#include "../externs.h"
#include "../mcpe/Player.h"

namespace Player
{
void getEntity(CScriptVar* jsfunc, void*)
{
	// TODO: this doesn't work since CScriptVar doesn't have a uint64_t constructor
	jsfunc->setReturnVar(new CScriptVar((int) Entity$getUniqueID(MCPE_localplayer)));
}
};
