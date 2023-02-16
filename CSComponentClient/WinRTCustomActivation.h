#pragma once
#include <winrt/Windows.Foundation.h>

int32_t __stdcall custom_winrt_activation_handler(void* classId, winrt::guid const& guid, void** result) noexcept;