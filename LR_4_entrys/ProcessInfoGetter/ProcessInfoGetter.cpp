#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
using namespace std;

int main() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        cerr << "Error creating process snapshot. Error Code: " << GetLastError() << endl;
        return 1;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &processEntry)) {
        do {
            cout << "Process ID: " << processEntry.th32ProcessID << "\t";
            cout << "Process Name: " << processEntry.szExeFile << endl;
        } while (Process32Next(snapshot, &processEntry));
    }
    else {
        cerr << "Error retrieving process information. Error Code: " << GetLastError() << endl;
    }

    CloseHandle(snapshot);

    return 0;
}