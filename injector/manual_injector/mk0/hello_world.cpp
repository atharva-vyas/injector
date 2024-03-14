#include <iostream>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <thread>

extern "C" __declspec(dllexport) void __stdcall HelloWorld() {
    std::ofstream file("C:\\Users\\W10-LegionPro5i\\Documents\\code\\injector\\mk0\\counter.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    int counter = 0;

    while (true)
    {
        file << "Counter: " << counter++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    

    file.close();
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
