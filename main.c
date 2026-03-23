/*
 * Mouse Dancing — move o cursor 1px a cada 15s (ida e volta) e mostra ícone na bandeja.
 * Win32 apenas: user32 + shell32.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define WM_TRAY (WM_USER + 100)
#define ID_TIMER_JIGGLE 1
#define ID_MENU_EXIT 1

static NOTIFYICONDATA g_nid;
static const TCHAR kClassName[] = TEXT("MouseDancingTrayWnd");

static void JiggleOnce(void) {
    POINT pt;
    static int dir = 1;

    if (!GetCursorPos(&pt)) {
        return;
    }
    SetCursorPos(pt.x + dir, pt.y);
    dir = -dir;
}

static void RemoveTrayIcon(HWND hwnd) {
    (void)hwnd;
    Shell_NotifyIcon(NIM_DELETE, &g_nid);
    ZeroMemory(&g_nid, sizeof(g_nid));
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        NOTIFYICONDATA nid = {0};
        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hwnd;
        nid.uID = 1;
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        nid.uCallbackMessage = WM_TRAY;
        nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        lstrcpy(nid.szTip, TEXT("Mouse Dancing — em execução"));
        if (!Shell_NotifyIcon(NIM_ADD, &nid)) {
            return -1;
        }
        g_nid = nid;
        SetTimer(hwnd, ID_TIMER_JIGGLE, 15000, NULL);
        return 0;
    }
    case WM_TIMER:
        if (wParam == ID_TIMER_JIGGLE) {
            JiggleOnce();
        }
        return 0;
    case WM_TRAY:
        if (lParam == WM_RBUTTONUP) {
            POINT pt;
            HMENU hMenu;
            GetCursorPos(&pt);
            hMenu = CreatePopupMenu();
            if (!hMenu) {
                break;
            }
            AppendMenu(hMenu, MF_STRING, ID_MENU_EXIT, TEXT("Sair"));
            SetForegroundWindow(hwnd);
            TrackPopupMenu(hMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hwnd, NULL);
            DestroyMenu(hMenu);
            PostMessage(hwnd, WM_NULL, 0, 0);
        }
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_MENU_EXIT) {
            DestroyWindow(hwnd);
        }
        return 0;
    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER_JIGGLE);
        RemoveTrayIcon(hwnd);
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG msg;

    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = kClassName;
    if (!RegisterClass(&wc)) {
        return 1;
    }

    hwnd = CreateWindowEx(0, kClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
    if (!hwnd) {
        return 1;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
