#pragma once

#include "Class.g.h"

namespace winrt::CppComponent::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        hstring Hello();
    };
}

namespace winrt::CppComponent::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
