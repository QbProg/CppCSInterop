#include "pch.h"
#include "Class.h"
#include "Class.g.cpp"

namespace winrt::CppComponent::implementation
{
    hstring Class::Hello()
    {
        return L"Hello from C++";
    }
}
