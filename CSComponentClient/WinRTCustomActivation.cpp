#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::Foundation;

int32_t __stdcall custom_winrt_activation_handler(void* classId, winrt::guid const& guid, void** result) noexcept
{
    using namespace winrt::impl;
    using namespace winrt;

    winrt::hstring name; winrt::copy_from_abi(name, classId);

    /* Note : this code is mostly copied from base.h and customized to allow an additional probing of the DLL */

    static int32_t(__stdcall* handler)(void* classId, winrt::guid const& iid, void** factory) noexcept;
    impl::load_runtime_function(L"combase.dll", "RoGetActivationFactory", handler, fallback_RoGetActivationFactory);
    hresult hr = handler(*(void**)(&name), guid, result);

    if (hr == impl::error_not_initialized)
    {
        auto usage = reinterpret_cast<int32_t(__stdcall*)(void** cookie) noexcept>(WINRT_IMPL_GetProcAddress(WINRT_IMPL_LoadLibraryW(L"combase.dll"), "CoIncrementMTAUsage"));

        if (!usage)
        {
            return hr;
        }

        void* cookie;
        usage(&cookie);
        hr = handler(*(void**)(&name), guid, result);
    }

    if (hr == 0)
    {
        return 0;
    }

    com_ptr<IErrorInfo> error_info;
    WINRT_IMPL_GetErrorInfo(0, error_info.put_void());

    std::wstring path{ static_cast<hstring const&>(name) };
    std::size_t count{};

    while (std::wstring::npos != (count = path.rfind('.')))
    {
        path.resize(count);
        path += L".dll";
        library_handle library(WINRT_IMPL_LoadLibraryW(path.c_str()));
        path.resize(path.size() - 4);

        bool fail = false;
        if (!library)
        {
            fail = true;
        }

        auto library_call = reinterpret_cast<int32_t(__stdcall*)(void* classId, void** factory)>(WINRT_IMPL_GetProcAddress(library.get(), "DllGetActivationFactory"));

        if (!library_call)
        {
            fail = true;
        }

        /** Custom code to handle custom .Host.dll activation */
        if (fail)
        {
            path += L".Host.dll";
            library = library_handle(WINRT_IMPL_LoadLibraryW(path.c_str()));
            path.resize(path.size() - 4 - 5);

            if (!library)
                continue;
            
            library_call = reinterpret_cast<int32_t(__stdcall*)(void* classId, void** factory)>(WINRT_IMPL_GetProcAddress(library.get(), "DllGetActivationFactory"));

            if (!library_call)
                continue;
        }

        com_ptr<abi_t<Windows::Foundation::IActivationFactory>> library_factory;

        if (0 != library_call(*(void**)(&name), library_factory.put_void()))
        {
            continue;
        }

        bool isSameInterfaceAsIActivationFactory = (winrt::guid_of<Windows::Foundation::IActivationFactory>() == guid);
        if (isSameInterfaceAsIActivationFactory)
        {
            *result = library_factory.detach();
            library.detach();
            return 0;
        }
        else if (0 == library_factory.as(guid, result))
        {
            library.detach();
            return 0;
        }
    }

    WINRT_IMPL_SetErrorInfo(0, error_info.get());
    return hr;
}
