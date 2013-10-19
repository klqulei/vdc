// vtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "debug.hpp"

using namespace UtilityLib;

int _tmain(int argc, _TCHAR* argv[])
{
	Debug::init(0);
	int i = 0;

	while(1)
	{
		Debug::DebugPrint("While %d\n", i ++);
		Sleep(1000);
	}
	return 0;
}

