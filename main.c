/*
 * Mouse Dancing — move o cursor 1px a cada 15s (ida e volta) e mostra ícone na bandeja.
 * Win32 apenas: user32 + shell32. Compilar sempre com UNICODE (ver build.bat).
 */
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <wchar.h>
#if defined(__GNUC__) && !defined(_MSC_VER)
#include <stdio.h>
#endif

#define WM_TRAY (WM_USER + 100)
#define ID_TIMER_JIGGLE 1
#define ID_MENU_ABOUT 2
#define ID_MENU_EXIT 1

/* Alinhar com releases / instalador quando atualizares */
#define MOUSE_DANCING_VERSION L"0.0.3"

static NOTIFYICONDATAW g_nid;
static BOOL g_trayIconMustDestroy;
static const wchar_t kClassName[] = L"MouseDancingTrayWnd";

static void JiggleOnce(void) {
    POINT pt;
    static int dir = 1;

    if (!GetCursorPos(&pt)) {
        return;
    }
    SetCursorPos(pt.x + dir, pt.y);
    dir = -dir;
}

static HICON LoadTrayIcon(void) {
    SHSTOCKICONINFO sii;

    ZeroMemory(&sii, sizeof(sii));
    sii.cbSize = sizeof(sii);
    /* Ícone de “relógio” (timer) no Windows 10+; Win7 antigo pode falhar. */
    if (SUCCEEDED(SHGetStockIconInfo((SHSTOCKICONID)101, SHGFI_ICON | SHGFI_SMALLICON, &sii))) {
        g_trayIconMustDestroy = TRUE;
        return sii.hIcon;
    }
    ZeroMemory(&sii, sizeof(sii));
    sii.cbSize = sizeof(sii);
    if (SUCCEEDED(SHGetStockIconInfo(SIID_INFO, SHGFI_ICON | SHGFI_SMALLICON, &sii))) {
        g_trayIconMustDestroy = TRUE;
        return sii.hIcon;
    }
    g_trayIconMustDestroy = FALSE;
    return LoadIconW(NULL, (LPCWSTR)IDI_APPLICATION);
}

static void RemoveTrayIcon(HWND hwnd) {
    (void)hwnd;
    Shell_NotifyIconW(NIM_DELETE, &g_nid);
    if (g_trayIconMustDestroy && g_nid.hIcon) {
        DestroyIcon(g_nid.hIcon);
        g_trayIconMustDestroy = FALSE;
    }
    ZeroMemory(&g_nid, sizeof(g_nid));
}

static void ShowAbout(HWND hwnd) {
    wchar_t buf[768];

    /* Literais em \\u — correctos em qualquer codepage do ficheiro; ver /utf-8 no build. */
#if defined(_MSC_VER)
    swprintf_s(buf, 768,
               L"Estado: em execu\u00E7\u00E3o.\n\nVers\u00E3o: %ls\n\n"
               L"O cursor move 1 pixel a cada 15 segundos (ida e volta) para reduzir o bloqueio "
               L"autom\u00E1tico do Windows por inatividade.\n\n"
               L"Bot\u00E3o direito no \u00EDcone para Sair ou Sobre.",
               MOUSE_DANCING_VERSION);
#else
    swprintf(buf, 768,
             L"Estado: em execu\u00E7\u00E3o.\n\nVers\u00E3o: %ls\n\n"
             L"O cursor move 1 pixel a cada 15 segundos (ida e volta) para reduzir o bloqueio "
             L"autom\u00E1tico do Windows por inatividade.\n\n"
             L"Bot\u00E3o direito no \u00EDcone para Sair ou Sobre.",
             MOUSE_DANCING_VERSION);
#endif
    MessageBoxW(hwnd, buf, L"Mouse Dancing", MB_ICONINFORMATION | MB_OK);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        NOTIFYICONDATAW nid = {0};

        g_trayIconMustDestroy = FALSE;
        nid.cbSize = sizeof(NOTIFYICONDATAW);
        nid.hWnd = hwnd;
        nid.uID = 1;
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        nid.uCallbackMessage = WM_TRAY;
        nid.hIcon = LoadTrayIcon();
        wcsncpy(nid.szTip,
                L"Mouse Dancing \u2014 em execu\u00E7\u00E3o (clique para informa\u00E7\u00F5es)",
                127);
        nid.szTip[127] = L'\0';
        if (!Shell_NotifyIconW(NIM_ADD, &nid)) {
            if (g_trayIconMustDestroy && nid.hIcon) {
                DestroyIcon(nid.hIcon);
                g_trayIconMustDestroy = FALSE;
            }
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
        if (lParam == WM_LBUTTONUP) {
            ShowAbout(hwnd);
        } else if (lParam == WM_RBUTTONUP) {
            POINT pt;
            HMENU hMenu;

            GetCursorPos(&pt);
            hMenu = CreatePopupMenu();
            if (!hMenu) {
                break;
            }
            AppendMenuW(hMenu, MF_STRING, ID_MENU_ABOUT, L"Sobre o Mouse Dancing\u2026");
            AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
            AppendMenuW(hMenu, MF_STRING, ID_MENU_EXIT, L"Sair");
            SetForegroundWindow(hwnd);
            TrackPopupMenu(hMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hwnd, NULL);
            DestroyMenu(hMenu);
            PostMessageW(hwnd, WM_NULL, 0, 0);
        }
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_MENU_ABOUT:
            ShowAbout(hwnd);
            break;
        case ID_MENU_EXIT:
            DestroyWindow(hwnd);
            break;
        default:
            break;
        }
        return 0;
    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER_JIGGLE);
        RemoveTrayIcon(hwnd);
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    WNDCLASSW wc = {0};
    HWND hwnd;
    MSG msg;

    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = kClassName;
    if (!RegisterClassW(&wc)) {
        return 1;
    }

    hwnd = CreateWindowExW(0, kClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
    if (!hwnd) {
        return 1;
    }

    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}
