#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

static HHOOK hook;
static LPCSTR pathToFile;

static LRESULT HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
        goto callNext;

    if (wParam != WM_KEYDOWN)
        goto callNext;

    PlaySoundA(pathToFile, NULL, SND_FILENAME | SND_ASYNC);
    return 0;

callNext:
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    pathToFile = pCmdLine;
    hook = SetWindowsHookExA(WH_KEYBOARD_LL, HookProc, NULL, 0);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
    }

    UnhookWindowsHookEx(hook);

    return 0;
}
