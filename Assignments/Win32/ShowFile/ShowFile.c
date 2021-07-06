#include<Windows.h>
#include<stdio.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

#define BUFFER_SIZE 256
#define LINE_NUMBER_BUFFER_SIZE 16

#define X_START 0
#define X_OFFSET_1 4

#define FAIL_EXIT_IF(COND, MSG, CAPTION)        do\
                                                {\
                                                    if((COND)==TRUE)\
                                                    {\
                                                        MessageBox(NULL, TEXT(MSG), TEXT(CAPTION), MB_ICONERROR);\
                                                        ExitProcess(EXIT_FAILURE);\
                                                    }\
                                                }\
                                                while(0)


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

FILE* gfpDebug = NULL;
LPSTR glpCmdLine = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The Standard Window");
    static TCHAR szWindowCaption[] = TEXT("OneFileRead");

    HWND hWnd = NULL;
    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon =NULL;
    HICON hIconSm = NULL;
    ATOM bIsRegistered = 0;

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    gfpDebug = fopen("Debug.txt","w");
    FAIL_EXIT_IF((gfpDebug==NULL), "Failed to create a debug file", "fopen");
    glpCmdLine = lpCmdLine;

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    FAIL_EXIT_IF(hBrush == NULL, "Failed to load brush", "GetStockObject");

    hCursor = LoadCursor(NULL, IDC_ARROW);
    FAIL_EXIT_IF(hCursor == NULL, "Failed to load cursor", "LoadCursor");

    hIcon = LoadIcon(NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIcon == NULL, "Failed to load icon", "LoadIcon");

    hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIconSm == NULL, "Failed to load small icon", "LoadIcon"); 

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hInstance = hInstance;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    bIsRegistered = RegisterClassEx(&wndEx);
    FAIL_EXIT_IF(bIsRegistered == 0, "Failed to register class", "Register class ex");

    hWnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, szWindowCaption,
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);
    FAIL_EXIT_IF(hWnd==NULL, "Failed to create application window", "CreateWindowEx");

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    fclose(gfpDebug);
    gfpDebug = NULL;
    return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    static int cxChar, cyChar, cxCaps;
    HDC hdc = NULL;
    TEXTMETRIC tm;
    PAINTSTRUCT ps;
    FILE *fp = NULL;
    char chBuffer[BUFFER_SIZE];
    char chLineNumberBuffer[LINE_NUMBER_BUFFER_SIZE];
    char *pchBuffer = NULL;
    int iCnt;

    switch(uMsg)
    {
        case WM_CREATE:
            hdc = GetDC(hWnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3 :2) *cxChar/2;
            ReleaseDC(hWnd,hdc);
            hdc = NULL;
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            fp = fopen((CHAR*)glpCmdLine, "r");
            FAIL_EXIT_IF(fp == NULL,"Could not open given file", "fopen");
            iCnt = 0;
            memset(chBuffer, 0 , BUFFER_SIZE);
            memset(chLineNumberBuffer, 0, LINE_NUMBER_BUFFER_SIZE);
            while(fgets(chBuffer, BUFFER_SIZE, fp) != NULL)
            {
                pchBuffer = itoa(iCnt+1, chLineNumberBuffer, 10);
                TextOutA(hdc, X_START, iCnt*cyChar, pchBuffer, strlen(pchBuffer));
                TextOutA(hdc, X_OFFSET_1 * cxCaps, iCnt*cyChar, chBuffer, strlen(chBuffer));
                memset(chBuffer, 0 , BUFFER_SIZE);
                memset(chLineNumberBuffer, 0, LINE_NUMBER_BUFFER_SIZE);
                iCnt = iCnt + 1;
            }
            EndPaint(hWnd, &ps);
            hdc = NULL;
            fclose(fp);
            fp = NULL;
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}
