#include <iostream>
#include <windows.h>

typedef const char* (*HelloWorldFunc)();

int main()
{
    HMODULE dllHandle = LoadLibrary("test.dll");

    if (dllHandle != nullptr)
    {
        HelloWorldFunc helloWorldFunc = reinterpret_cast<HelloWorldFunc>(GetProcAddress(dllHandle, "HelloWorld"));

        if (helloWorldFunc != nullptr)
        {
            const char* result = helloWorldFunc();
            std::cout << "DLL says: " << result << std::endl;
        }
        else
        {
            std::cerr << "Failed to get function address." << std::endl;
        }

        FreeLibrary(dllHandle);
    }
    else
    {
        std::cerr << "Failed to load DLL." << std::endl;
    }

    return 0;
}
