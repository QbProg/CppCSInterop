#include <winrt/CSComponent.h>
#include "iostream"
#include "WinRTCustomActivation.h"

using namespace winrt;
using namespace Windows::Foundation;

extern "C" __declspec(dllexport) void dll_main()
{
	init_apartment();
	winrt_activation_handler = custom_winrt_activation_handler;

	CSComponent::CSClass ex;
	
	std::wcout << ex.Hello().c_str() << std::endl;

	/* This function in the C# component uses the other CppComponent! */
	std::wcout << ex.HelloRecallCpp().c_str() << std::endl;
}
