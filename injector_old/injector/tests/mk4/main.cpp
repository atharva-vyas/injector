// main.cpp

#include <iostream>
#include <Windows.h>

typedef void (*HelloWorldFunc)();

int main() {
    HINSTANCE hDll = LoadLibrary("hello_world.dll");
    if (hDll == NULL) {
        std::cerr << "Error loading DLL." << std::endl;
        return 1;
    }

    HelloWorldFunc helloWorld = (HelloWorldFunc)GetProcAddress(hDll, "HelloWorld");
    if (helloWorld == NULL) {
        std::cerr << "Error getting function address." << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    // Call the function from the DLL
    helloWorld();

    // Unload the DLL
    FreeLibrary(hDll);

    return 0;
}
