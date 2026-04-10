#define NOMINMAX

#define _WIN32_WINNT 0x0601
#define WINVER 0x0601

#include <windows.h>
#include <cstring>
#include <iostream>

#include "resource.h"
#include "globals.h"
#include "bitmapUtils.h"
#include "RandomFunctionsIFound.h"
#include "Strings/StringFunctions.h"
char g_path_Levels[1024];
char g_path_Fend[1024];
char g_path_Scene[1024];
char g_path_Wheel[1024];
char g_path_Intro[1024];
char g_path_Ending[1024];
char g_path_Demos[1024];
char g_path_Music[1024];
char g_path_Voices[1024];
char g_path_References[1024];
char g_path_Bonus[1024];
HINSTANCE ghInstance = NULL;
LOGFONTA GLOBAL_FONT = { 0 };
int g_filesBytreRead;
int get_lang_bitmask() {
    LANGID langid;
    int lang_bitmask;

    langid = GetUserDefaultLangID();
    switch (langid & 0xff) {
        case 7:
            lang_bitmask = 4;
            break;
        default:
            lang_bitmask = 2;
            break;
        case 9:
            lang_bitmask = 1;
            break;
        case 10:
            lang_bitmask = 0x10;
            break;
        case 0xc:
            lang_bitmask = 2;
            break;
        case 0x10:
            lang_bitmask = 0x20;
            break;
        case 0x13:
            lang_bitmask = 8;
            break;
        case 0x16:
            lang_bitmask = 0x40;
    }
    return lang_bitmask;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    // TODO: Understand how the fuck does the game actually get the name as i cannot find it in the strings or resources
    LPCSTR modal_title = "Sheep Raider Decomp";

    switch (message) {
        case WM_ERASEBKGND: {
            HDC hdc = (HDC)wParam;

            // Load bitmap (resource ID 115 = 0x73)
            HBITMAP hBitmap = LoadBitmapA(ghInstance, MAKEINTRESOURCE(115));
            if (!hBitmap)
                return FALSE;

            BITMAP bm;
            GetObjectA(hBitmap, sizeof(BITMAP), &bm);

            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

            // Blit bitmap to dialog background
            BitBlt(
                hdc,
                0, 0,
                bm.bmWidth,
                bm.bmHeight,
                hdcMem,
                0, 0,
                SRCCOPY
            );

            // Cleanup
            SelectObject(hdcMem, hOld);
            DeleteDC(hdcMem);
            DeleteObject(hBitmap);

            return TRUE;
        }
        case WM_INITDIALOG:
            {
            SetWindowTextA(hDlg, modal_title);
            struct ButtonInfo {
                int id;
                int bmpId;
                COLORREF color;
            };

            ButtonInfo buttons[] = {
                {1100, 145, 0x000000},
                {1102, 145, 0x000000},
                {1103, 145, 0x000000},
                {1104, 145, 0x000000},
                {1105, 145, 0x000000},
                {1106, 145, 0x000000},
                {1108, 145, 0x000000},
                {1101, 146, 0xF6EEEE}, // Play
                {1109, 146, 0xF6EEEE}, //Quit
            };

            for (auto& b : buttons)
            {
                char text[256];
                GetDlgItemText(hDlg, b.id, text, sizeof(text));

                HBITMAP hBmp = drawTextOverBitmap(hDlg, b.bmpId, text, b.color);

                HWND hBtn = GetDlgItem(hDlg, b.id);
                SendMessage(hBtn, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
            }
            return TRUE;
    }

        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED)
            {
                // Extract the original control ID
                int raw_id = LOWORD(wParam);

                // Apply the same offset as the original program
                int clicked_button_id = raw_id - 1100; // 0x44C

                switch (clicked_button_id)
                {
                    case 0:
                        // corresponds to button ID 1100
                        MessageBoxA(hDlg, "Install DirectX btn", "Info", MB_OK);
                        break;

                    case 1:
                        // corresponds to button ID 1101 (Play in your mapping)

                        EndDialog(hDlg, 0);
                        break;

                        break;

                    case 9:
                        // corresponds to button ID 1109 (Quit)
                        EndDialog(hDlg, 1);
                        break;

                    default:
                        break;
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}




int create_window(HINSTANCE hInstance) {
    HWND hWnd;
    WNDCLASS wc = {};

    char CLASS_NAME[256];
    char local_exeDir [512];


    GetExeDirectory(local_exeDir);
    custom_strcopy(g_path_Levels,local_exeDir);
    custom_strcopy(g_path_Scene,local_exeDir);
    custom_strcopy(g_path_Wheel,local_exeDir);
    custom_strcopy(g_path_Intro,local_exeDir);
    custom_strcopy(g_path_Fend,local_exeDir);
    custom_strcopy(g_path_Ending,local_exeDir);
    custom_strcopy(g_path_Demos,local_exeDir);
    custom_strcopy(g_path_Music,local_exeDir);
    custom_strcopy(g_path_Voices,local_exeDir);
    custom_strcopy(g_path_References,local_exeDir);
    custom_strcopy(g_path_Bonus,local_exeDir);
    custom_strcat(g_path_Levels, "\\Levels\\Lvl-%02d\\Lvl-%02d");
    custom_strcat(g_path_Scene, "\\Levels\\Scene\\Scene");
    custom_strcat(g_path_Wheel, "\\Levels\\Wheel\\Wheel");
    custom_strcat(g_path_Intro, "\\Levels\\Intro\\Intro");
    custom_strcat(g_path_Fend, "\\Levels\\Fend\\Fend");
    custom_strcat(g_path_Ending, "\\Levels\\Ending\\Ending");
    custom_strcat(g_path_Demos, "\\Levels\\Demos");
    custom_strcat(g_path_Music, "\\Musics\\");
    custom_strcat(g_path_Voices, "\\Voices\\");
    custom_strcat(g_path_References, "\\References\\");
    custom_strcat(g_path_Bonus, "\\Bonus\\");


    CLASS_NAME[0xFF - 1] = '\0';

    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLASS_NAME;

    ATOM class_id = RegisterClassA(&wc);
    if (class_id == 0) {
        MessageBoxA(NULL, "Unable to register window class: ", "SheepD3D ERROR", MB_ICONERROR);
        return 1;

    }

        g_hInstance = hInstance;

        hWnd = CreateWindowExA(
                0,
                CLASS_NAME,
                CLASS_NAME,
                WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                800,
                600,
                NULL,
                NULL,
                hInstance,
                NULL
        );

        if (hWnd == NULL) {
            MessageBoxA(NULL, "Unable to create rendering window", "SheepD3D ERROR", MB_ICONERROR);
            return 1;
        }

        /*if (!directx_checker_dialog()) {
            return 1;
        }*/

        // Init engine
        g_pEngine = new EngineState();
        if (g_pEngine == nullptr) {
            return 1;
        }
        //init_dx_device(hWnd, hInstance, 3);

        // Init DirectSound manager
        //DSManager *dsManager = new DSManager();
        //if (dsManager == nullptr) {
        //    g_pDSoundBuffer = nullptr;
        //} else {
        //    g_pDSoundBuffer = DSManager_Init(dsManager);
        //}

        //FUN_0040369c();

        // Launcher dialog - if user cancelled, exit
        int result = DialogBox(hInstance, MAKEINTRESOURCE(IDD_LAUNCHER), NULL, DialogProc);
        if (result != 1) {
            return 0;
        }
/*
        // Init DirectX
        HRESULT hResult = something_directx_is_here(g_pEngine);
        if (FAILED(hResult)) {
            const char *windowTitle = get_localized_string(&g_pLocalization, 1, lang_offset, 0x10);
            const char *windowText  = get_localized_string(&g_pLocalization, 8, lang_offset, 0x40);
            MessageBoxA(hWnd, windowText, windowTitle, MB_ICONERROR);
            return 1;
        }*/

        // Init DirectSound (22050 Hz, 16-bit)
        /*hResult = DS_CreateDevice(hWnd, 22050, 16);
        if (FAILED(hResult)) {
            const char *windowTitle = get_localized_string(&g_pLocalization, 1, lang_offset, 0x10);
            const char *windowText  = get_localized_string(&g_pLocalization, 8, lang_offset, 0x80);
            MessageBoxA(hWnd, windowText, windowTitle, MB_ICONERROR);
            return 1;
        }*/

        // Show main window and run game loop
        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //ReleaseDirectXObjects();
        delete g_pEngine;
        //delete dsManager;

        return 0;


}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    ghInstance = hInstance;
    // Get The actual font
    strcpy(GLOBAL_FONT.lfFaceName, "Tahoma");
    GLOBAL_FONT.lfHeight = -11;
    create_window(hInstance);

    return 0;
}
