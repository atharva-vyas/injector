// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "framework.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL, "hi", "haha", MB_OK);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// int main(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
//     DllMain(hModule, reason, lpReserved);
//     return 0;
// }


int main(void) {
    MessageBoxA(NULL, "hi", "haha", MB_OK);
}
