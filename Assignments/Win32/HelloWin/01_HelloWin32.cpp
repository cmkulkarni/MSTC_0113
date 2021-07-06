#include<Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE nPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("The First Window");
    static TCHAR szWindowCaption[] = TEXT("Hello Windows!");

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

    // hwnd = CreateWindowEx(
    //         WS_EX_APPWINDOW,
    //         szClassName,
    //         szWindowCaption,
    //         WS_OVERLAPPEDWINDOW,
    //         CW_USEDEFAULT,
    //         CW_USEDEFAULT,
    //         CW_USEDEFAULT,
    //         CW_USEDEFAULT,
    //         (HWND)NULL,
    //         hInstance,
    //         NULL
    //     );

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_OVERLAPPEDWINDOW,
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
    switch(uMsg){
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return(DefWindowProc(hwnd, uMsg, wParam, lParam));
}