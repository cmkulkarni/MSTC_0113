#include<Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE nPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("The Standard Window");
    static TCHAR szWindowCaption[] = TEXT("113_Chaitanya:- All Group Names");

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hwnd = NULL;

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Could not obtain brush"), TEXT("GetStockObject"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Could not obtain Cursor"), TEXT("LoadCurson"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Could not obtain Icon"), TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Could not obtain Icon small"), TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hInstance = hInstance;
    wndEx.lpfnWndProc = WndProc;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL, TEXT("Could Now register window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    if(hwnd == NULL){
        MessageBox((HWND)NULL, TEXT("Could not create Application window"), TEXT("CreateWindowEx"), MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, (HWND)(NULL), 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cyClient, cxClient, cxChar, cyChar;
    static TCHAR* ppszGroupName[] = {TEXT("Dennis Ritchie Group"), TEXT("Ken Thompson Group"), TEXT("Linus Torvald Group"),
                                    TEXT("Alan Turing Group"), TEXT("Jon Von Neumann Group"), TEXT("Lady Ada Lovelance Group"),
                                    TEXT("Donald Knuth Group"), TEXT("David Cutler Group"), TEXT("Helen Cluster Group")};
    HDC hdc =NULL;
    TEXTMETRIC tm;
    PAINTSTRUCT ps;

    switch(uMsg){
        case WM_CREATE:
            hdc = GetDC(hwnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd, hdc);
            hdc = NULL;
            break;
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            SetTextAlign(hdc, TA_LEFT | TA_TOP);
            TextOut(hdc, 0, 0, ppszGroupName[0], lstrlen(ppszGroupName[0]));

            SetTextAlign(hdc, TA_CENTER | TA_TOP);
            TextOut(hdc, cxClient/2, 0, ppszGroupName[1], lstrlen(ppszGroupName[1]));

            SetTextAlign(hdc, TA_RIGHT | TA_TOP);
            TextOut(hdc, cxClient, 0, ppszGroupName[2], lstrlen(ppszGroupName[2]));


            SetTextAlign(hdc, TA_LEFT | TA_TOP);
            TextOut(hdc, 0, cyClient/2, ppszGroupName[3], lstrlen(ppszGroupName[3]));

            SetTextAlign(hdc, TA_CENTER | TA_TOP);
            TextOut(hdc, cxClient/2, cyClient/2, ppszGroupName[4], lstrlen(ppszGroupName[4]));

            SetTextAlign(hdc, TA_RIGHT | TA_TOP);
            TextOut(hdc, cxClient, cyClient/2, ppszGroupName[5], lstrlen(ppszGroupName[5]));


            SetTextAlign(hdc, TA_LEFT | TA_BOTTOM);
            TextOut(hdc, 0, cyClient, ppszGroupName[6], lstrlen(ppszGroupName[6]));

            SetTextAlign(hdc, TA_CENTER | TA_BOTTOM);
            TextOut(hdc, cxClient/2, cyClient, ppszGroupName[7], lstrlen(ppszGroupName[7]));

            SetTextAlign(hdc, TA_RIGHT | TA_BOTTOM);
            TextOut(hdc, cxClient, cyClient, ppszGroupName[8], lstrlen(ppszGroupName[8]));

            EndPaint(hwnd, &ps);
            hdc = NULL;
            break;
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return(DefWindowProc(hwnd, uMsg, wParam, lParam));
}