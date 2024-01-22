#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    wchar_t rowSumCmd[] = L"C:\\repos\\LR_1\\x64\\Debug\\RowSumCalculator.exe";
    if (!CreateProcess(NULL, rowSumCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        cerr << "CreateProcess failed 1 (" << GetLastError() << ").\n";
        return 1;
    }

    wchar_t procInfoCmd[] = L"C:\\repos\\LR_1\\x64\\Debug\\ProcessInfoGetter.exe";
    if (!CreateProcess(NULL, procInfoCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        cerr << "CreateProcess failed 2 (" << GetLastError() << ").\n";
        return 1;
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return 0;
}
