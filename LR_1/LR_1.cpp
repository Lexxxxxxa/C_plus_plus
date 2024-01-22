#include <windows.h>

const wchar_t g_szClassName[] = L"myWindowClass";
HWND hKeyDisplay; 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Віконний клас не був зареєстрований!", L"Помилка!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        L"Відображення натисканої клавіші",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 250, 
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Вікно не було створено!", L"Помилка!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        CreateWindow(L"BUTTON", L"Вихід",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 10, 100, 24,
            hwnd, (HMENU)1, NULL, NULL);

        CreateWindow(L"BUTTON", L"Автор",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            120, 10, 100, 24,
            hwnd, (HMENU)2, NULL, NULL);

        hKeyDisplay = CreateWindow(L"STATIC", L"",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            50, 100, 400, 20, 
            hwnd, (HMENU)3, NULL, NULL);
    }
    break;
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) 
        {
            PostQuitMessage(0);
        }
        else if (LOWORD(wParam) == 2) 
        {
            MessageBox(hwnd, L"Автор: Зубцов О.В.", L"Інформація про автора:", MB_OK);
        }
    }
    break;
    case WM_KEYDOWN:
    {
        WCHAR keyText[50] = L"Натиснуто клавішу: ";
        if ((wParam >= 'A' && wParam <= 'Z') || (wParam >= '0' && wParam <= '9'))
        {
            WCHAR key[2] = { (WCHAR)wParam, L'\0' };
            wcscat_s(keyText, key);
        }
        else
        {
            switch (wParam)
            {
            case VK_ESCAPE:
                wcscat_s(keyText, L"ESC");
                break;
            case VK_RETURN:
                wcscat_s(keyText, L"Enter");
                break;
            case VK_BACK:
                wcscat_s(keyText, L"Backspace");
                break;
            case VK_CONTROL:
                wcscat_s(keyText, L"Ctrl");
                break;
            case VK_TAB:
                wcscat_s(keyText, L"TAB");
                break;
            case VK_SPACE:
                wcscat_s(keyText, L"Spacebar");
                break;
            }
        }

        SetWindowText(hKeyDisplay, keyText);
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}