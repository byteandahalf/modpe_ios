#include <iostream>

#include "../TinyJS.h"

#include "../externs.h"

void print(CScriptVar* jsfunc, void*)
{
	// TODO: make this an iOS alert
	std::cout << jsfunc->getParameter("text")->getString() << "\n";
}

void preventDefault(CScriptVar* jsfunc, void*)
{
	PREVENTDEFAULT = true;
}
