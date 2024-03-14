// #include "pch.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

void writeToFile() {
    // File stream
    std::ofstream file;

    // Open the file in append mode
    file.open("example.txt", std::ios::app);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit;
    }

    // Append a line to the file
    file << "This is a new line!" << std::endl;

    // Close the file (automatically closed when the stream goes out of scope)
    file.close();

    std::cout << "Line appended successfully." << std::endl;

    exit;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // std::cout << "Hello, World!" << std::endl;
        // MessageBoxA(NULL, "hi", "haha", MB_OK);
        writeToFile();
    case DLL_THREAD_ATTACH:
        writeToFile();
    case DLL_THREAD_DETACH:
        writeToFile();
    case DLL_PROCESS_DETACH:
        writeToFile();
        break;
    }
    return TRUE;
}
