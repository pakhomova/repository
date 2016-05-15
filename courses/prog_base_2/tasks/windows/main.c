#include <windows.h>
#include <CommCtrl.h>

#include "pensioner.h"

#define PENNUM 3

enum {
    BUTTON1_ID = 1,
    BUTTON2_ID,
    STATIC_ID
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    const char g_szClassName[] = "myWindowClass";

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Pensioner",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HINSTANCE hInst = GetModuleHandle(NULL);
    static HWND hStatic;
    static int currInd;
    static pensioner_t pensioners[PENNUM];

    switch(msg)
    {

        case WM_CREATE:
            CreateWindowEx(0,
                              WC_BUTTON,
                              "Next",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                              200, 50, 130, 23,
                              hwnd,
                              (HMENU)BUTTON1_ID,
                              hInst,
                              NULL);
            CreateWindowEx(0,
                              WC_BUTTON,
                              "Previous",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                              200, 100, 130, 23,
                              hwnd,
                              (HMENU)BUTTON2_ID,
                              hInst,
                              NULL);
            hStatic = CreateWindowEx(0,
                              WC_STATIC,
                              "Label",
                              WS_CHILD | WS_VISIBLE,
                              50, 10, 130, 140,
                              hwnd,
                              (HMENU)STATIC_ID,
                              hInst,
                              NULL);
            currInd = 0;
            pensioners[0] = pensioner_fill("Zhenya", "Pakhomova", "19.03.1998", 2000.7, 23);
            pensioners[1] = pensioner_fill("Petro", "Petrenko", "21.05.1998", 1200.3, 12);
            pensioners[2] = pensioner_fill("Ivan", "Ivanov", "1.12.1994", 1000, 17);
            SetWindowText(hStatic, pensioner_print(&pensioners[currInd]));
            break;
        case WM_COMMAND:
        switch (LOWORD(wParam)) {

		case BUTTON1_ID: {
		    if (currInd < PENNUM - 1)
                currInd++;

			SetWindowText(hStatic, pensioner_print(&pensioners[currInd]));
			break;
		}
		case BUTTON2_ID: {
		    if (currInd > 0) currInd--;

			SetWindowText(hStatic, pensioner_print(&pensioners[currInd]));
			break;
		}

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
