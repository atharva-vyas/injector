#include <iostream>
#include <Windows.h>

// extern "C" __declspec(dllexport) void HelloWorld() {
//     std::cout << "Hello, World!" << std::endl;
//     MessageBox(NULL, "Hello, World!", "Hello World Program", MB_OK);
// }

extern "C" __declspec(dllexport) void HelloWorld() {
    // MessageBoxA(NULL, "Hello, World!", "DLL Message", MB_OK);
    Sleep(3000);  // Sleep for 3 seconds
    MessageBoxW(NULL, L"Hello, World!", L"DLL Message", MB_OK);
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
