// injector.cpp

#include <Windows.h>
#include <iostream>

int main() {
    const char* dllPath = "hello_world.cpp"; // Replace with the actual path to your DLL

    DWORD processId;
    std::cout << "Enter the target process ID: ";
    std::cin >> processId;

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (hProcess == NULL) {
        std::cerr << "Error opening process. Make sure you have the correct process ID and necessary permissions. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    LPVOID remoteBuffer = VirtualAllocEx(hProcess, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (remoteBuffer == NULL) {
        std::cerr << "Error allocating memory in the target process. Error code: " << GetLastError() << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    if (!WriteProcessMemory(hProcess, remoteBuffer, dllPath, strlen(dllPath) + 1, NULL)) {
        std::cerr << "Error writing DLL path to the target process. Error code: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, remoteBuffer, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    HMODULE kernel32 = GetModuleHandle("kernel32.dll");
    if (kernel32 == NULL) {
        std::cerr << "Error getting handle to kernel32.dll. Error code: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, remoteBuffer, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    FARPROC loadLibrary = GetProcAddress(kernel32, "LoadLibraryA");
    if (loadLibrary == NULL) {
        std::cerr << "Error getting address of LoadLibraryA. Error code: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, remoteBuffer, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    // HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, remoteBuffer, 0, NULL);
    // if (hRemoteThread == NULL) {
    //     std::cerr << "Error creating remote thread. Error code: " << GetLastError() << std::endl;
    //     VirtualFreeEx(hProcess, remoteBuffer, 0, MEM_RELEASE);
    //     CloseHandle(hProcess);
    //     return 1;
    // }
    HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, remoteBuffer, 0, NULL);
    if (hRemoteThread == NULL) {
        std::cerr << "Error creating remote thread. Error code: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, remoteBuffer, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    // Wait for the remote thread to finish
    // WaitForSingleObject(hRemoteThread, INFINITE);
    // DWORD waitResult = WaitForSingleObject(hRemoteThread, INFINITE);
    // if (waitResult == WAIT_FAILED) {
    //     std::cerr << "Error waiting for remote thread. Error code: " << GetLastError() << std::endl;
    //     // Handle accordingly
    // }
// ...

// Wait for the remote thread to finish
    DWORD waitResult = WaitForSingleObject(hRemoteThread, INFINITE);

    if (waitResult == WAIT_OBJECT_0) {
        // The wait was successful
        std::cout << "DLL injected successfully." << std::endl;
    } else if (waitResult == WAIT_FAILED) {
        // An error occurred during the wait
        std::cerr << "Error waiting for remote thread. Error code: " << GetLastError() << std::endl;
    } else {
        // Unexpected wait result
        std::cerr << "Unexpected wait result: " << waitResult << " Error code: " << GetLastError() << std::endl;
    }

    // Close handles
    VirtualFreeEx(hProcess, remoteBuffer, 0, MEM_RELEASE);
    CloseHandle(hRemoteThread);
    CloseHandle(hProcess);
    return 0;


    // Check if the injection was successful
    DWORD exitCode;
    if (GetExitCodeThread(hRemoteThread, &exitCode) && exitCode != 0) {
        std::cout << "DLL injected successfully." << std::endl;
    } else {
        std::cerr << "DLL injection failed. Remote thread exit code: " << exitCode << " Error code: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
