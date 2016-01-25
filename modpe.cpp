#include "TinyJS.h"
#include "TinyJS_Functions.h"
#include "TinyJS_MathFunctions.h"

#include <sys/stat.h>
#include <stdio.h>
#include <sstream>

#include <Forklift/Forklift.h>


static CTinyJS* interpreter;


void print(CScriptVar* pars, void*)
{
	// TODO: iOS alert
	std::cout << pars->getParameter("text")->getString() << "\n";
}


void runTestScript()
{
	const char* path = "var/mobile/Media/script.js";

	struct stat results;
	if(!stat(path, &results) == 0) {
		printf("Cannot stat file! '%s'\n", path);
		return;
	}

	int size = results.st_size;
	FILE* file = fopen(path, "rb");
	if(!file) {
		printf("Unable to open file! '%s'\n", path);
		return;
	}

	char* buffer = new char[size + 1];
	long actualRead = fread(buffer, 1, size, file);
	buffer[actualRead] = 0;
	buffer[size] = 0;
	fclose(file);

	try {
		interpreter->execute(buffer);
	} catch (CScriptException* e) {
		printf("ERROR: %s\n", e->text.c_str());
	}

	delete[] buffer;
}

void initScriptCalls()
{
	interpreter->addNative("function print(text)", print, interpreter);
}

void initPointers()
{

}

void initInterpreter()
{
	interpreter = new CTinyJS();
	registerFunctions(interpreter);
	registerMathFunctions(interpreter);

	registerScriptCalls();
	initPointers();
}

MSInitialize // called when the process is loaded into MCPE
{
	initInterpreter();



	runTestScript();
}
