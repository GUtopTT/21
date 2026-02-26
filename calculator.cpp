#include <windows.h>
#include <stdio.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_ADD   201
#define ID_SUB   202
#define ID_MUL   203
#define ID_DIV   204

HWND hEdit1, hEdit2;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch(msg) {

    case WM_CREATE:
        CreateWindow("STATIC","Please input two numbers",
            WS_VISIBLE | WS_CHILD,
            30,20,190,20,
            hwnd,NULL,NULL,NULL);

        hEdit1 = CreateWindow("EDIT","",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            30,50,190,25,
            hwnd,(HMENU)ID_EDIT1,NULL,NULL);

        hEdit2 = CreateWindow("EDIT","",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            30,85,190,25,
            hwnd,(HMENU)ID_EDIT2,NULL,NULL);

        CreateWindow("BUTTON","+",
            WS_VISIBLE | WS_CHILD,
            30,130,40,30,
            hwnd,(HMENU)ID_ADD,NULL,NULL);

        CreateWindow("BUTTON","-",
            WS_VISIBLE | WS_CHILD,
            80,130,40,30,
            hwnd,(HMENU)ID_SUB,NULL,NULL);

        CreateWindow("BUTTON","*",
            WS_VISIBLE | WS_CHILD,
            130,130,40,30,
            hwnd,(HMENU)ID_MUL,NULL,NULL);

        CreateWindow("BUTTON","/",
            WS_VISIBLE | WS_CHILD,
            180,130,40,30,
            hwnd,(HMENU)ID_DIV,NULL,NULL);
        break;

    case WM_COMMAND:
    {
        char t1[100], t2[100], resultStr[100];
        double n1, n2, result;

        GetWindowText(hEdit1, t1, 100);
        GetWindowText(hEdit2, t2, 100);

        n1 = atof(t1);
        n2 = atof(t2);

        switch(LOWORD(wParam)) {

        case ID_ADD: result = n1 + n2; break;
        case ID_SUB: result = n1 - n2; break;
        case ID_MUL: result = n1 * n2; break;
        case ID_DIV:
            if(n2 == 0) {
                MessageBox(hwnd,"Cannot divide by zero","Error",MB_OK);
                return 0;
            }
            result = n1 / n2;
            break;
        default:
            return 0;
        }

        sprintf(resultStr,"%f",result);
        MessageBox(hwnd,resultStr,"Result",MB_OK);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return 0;
}


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
    wc.lpszClassName = "MyWindowClass";

    // สีชมพู
    wc.hbrBackground = CreateSolidBrush(RGB(0,255,255));

    if(!RegisterClassEx(&wc)) return 0;

    hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        250, 200,
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL) return 0;

    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
