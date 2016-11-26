#include <iostream>

#include "../TinyJS.h"
#include "../externs.h"

#include "../minecraftpe/MinecraftClient.h"

void print(CScriptVar* jsfunc, void*)
{
	// TODO: make this an iOS alert
	std::cout << jsfunc->getParameter("text")->getString() << "\n";
}

void clientMessage(CScriptVar* jsfunc, void*)
{
	GuiData$addMessage(MCPE_client->gui, "ModPE", jsfunc->getParameter("text")->getString(), 300, false);
}

void preventDefault(CScriptVar* jsfunc, void*)
{
	PREVENTDEFAULT = true;
}
