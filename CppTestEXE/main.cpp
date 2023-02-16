#include "windows.h"
#include <iostream>

extern "C" __declspec(dllimport) void dll_main();

int main()
{
	dll_main();
	return 0;
}