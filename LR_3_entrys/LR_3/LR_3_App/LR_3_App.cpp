// Main.cpp

#include <windows.h>
#include <iostream>
#include <MyLibrary.h>

typedef int (*AddFunction)(int, int);
typedef void (*DisplayMessageFunction)(const char*);

int main() {
    HMODULE hDll = LoadLibrary(L"LR_3.dll");

    if (hDll != NULL) {
        AddFunction addFunction = (AddFunction)GetProcAddress(hDll, "Add");
        DisplayMessageFunction displayMessageFunction = (DisplayMessageFunction)GetProcAddress(hDll, "DisplayMessage");

        if (addFunction != NULL && displayMessageFunction != NULL) {
            int result = addFunction(5, 3);
            std::cout << "Result of Add function: " << result << std::endl;

            displayMessageFunction("Hello from DLL!");
        }
        else {
            std::cerr << "Failed to get function addresses from DLL." << std::endl;
        }

        FreeLibrary(hDll);
    }
    else {
        std::cerr << "Failed to load DLL. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}