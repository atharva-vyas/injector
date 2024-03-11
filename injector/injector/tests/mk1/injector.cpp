#include <iostream>
#include <Windows.h>
#include <Tlhelp32.h>

DWORD GetProcId(const char* procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_stricmp(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
                
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}


int main() {
    const char* dllPath = "C:\\Users\\W10-LegionPro5i\\Documents\\code\\injector\\mk2\\cosmo.dll";
    // const char* procName = "javaw.exe";
    const char* procName = "firefox.exe";
    DWORD procId = 0;

    // LPCSTR dllPath;
    // dllPath = sDllPath.c_str();

    while (!procId) {
        procId = GetProcId(procName);
        Sleep(30);
    }
    
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
    
    if (hProc && hProc != INVALID_HANDLE_VALUE) {
        void * loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        
        if (loc) {
            WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
        }

        HANDLE hTread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hTread) {
            CloseHandle(hTread);
        }
    }
    

    if (hProc) {
        CloseHandle(hProc);
    }
    
    return 0;
}