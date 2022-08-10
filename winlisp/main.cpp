#include <windows.h>
#include <fstream>
#include <filesystem>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"
#include "listview.h"
#include "proc.h"

static TCHAR szAppName[] = TEXT("PoorMenu");

environment global_env;
PAINTSTRUCT ps;
std::vector<HINSTANCE> apps;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM registerclass(HINSTANCE hInstance, std::string app) {
    //static TCHAR szAppName[] = TEXT("HelloWin");
    WNDCLASS     wndclass = {0};
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = app.c_str();// szAppName;
    return RegisterClass(&wndclass);
}

bool haserror=false;
void PageGDICalls(HDC hdcPrn, int cxPage, int cyPage)
{
    static TCHAR szTextStr[] = TEXT("Hello, Printer!");

    Rectangle(hdcPrn, 0, 0, cxPage, cyPage);

    MoveToEx(hdcPrn, 0, 0, NULL);
    LineTo(hdcPrn, cxPage, cyPage);
    MoveToEx(hdcPrn, cxPage, 0, NULL);
    LineTo(hdcPrn, 0, cyPage);

    SaveDC(hdcPrn);

    SetMapMode(hdcPrn, MM_ISOTROPIC);//MM_ANISOTROPIC
    SetWindowExtEx(hdcPrn, 1000, 1000, NULL);
    SetViewportExtEx(hdcPrn, cxPage / 2, -cyPage / 2, NULL);
    SetViewportOrgEx(hdcPrn, cxPage / 2, cyPage / 2, NULL);
    SIZE size = { 0,0 };
    GetWindowExtEx(hdcPrn, &size);
    //MM_ISOTROPIC 各向同性的模式下，取得的Viewport Size和设置，通常是不同的。一遍保证横向纵向的比例正确。
    GetViewportExtEx(hdcPrn, &size);
    Ellipse(hdcPrn, -500, 500, 500, -500);

    SetTextAlign(hdcPrn, TA_BASELINE | TA_CENTER);
    TextOut(hdcPrn, 0, 0, szTextStr, lstrlen(szTextStr));

    RestoreDC(hdcPrn, -1);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    cell a;
    std::string str;    
    if(!haserror)
    try {
        
#pragma warning(push, 0)
        
#pragma warning(pop)
        str = "(winproc  ";
        str += para_hwnd_str(hwnd);
        str += " ";
        str += std::to_string(message);
        str += " ";
        str += std::to_string(wParam);
        str += " ";
        str += std::to_string(lParam);
        str += ")";
        a = run(str, &global_env);
        HWND hw = (HWND)((DWORD64)hwnd);
        /*if (message == WM_PAINT || message == WM_DESTROY) {*/
        if ( message == WM_DESTROY) {
            return 0;
        }
    }
    catch (std::string msg) {
        ofstream myFile_Handler;
        myFile_Handler.open("log.txt", std::ios_base::app);
        myFile_Handler << msg << endl;
        myFile_Handler.close();
        exit(2);
        haserror = true;
    }   
    
    static HWND hwndEdit = 0; std::stringstream str1;
    static int   cxClient, cyClient;
    HDC hdc;
    switch (message)
    {       

    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;
    //case WM_PAINT:
    //    hdc = BeginPaint(hwnd, &ps);

    //    PageGDICalls(hdc, cxClient, cyClient);

    //    EndPaint(hwnd, &ps);
    //    return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

HWND createwindow(HINSTANCE hInstance, std::string app) {
    //static TCHAR szAppName[] = TEXT("HelloWin");
    return  CreateWindow(app.c_str(),                   // window class name
        //TEXT("The Hello Program"), // window caption
        app.c_str(),
        WS_OVERLAPPEDWINDOW,        // window style
        //CW_USEDEFAULT,              // initial x position
        //CW_USEDEFAULT,              // initial y position
        //CW_USEDEFAULT,              // initial x size
        //CW_USEDEFAULT,              // initial y size
        100,100,
        600,400,
        NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL);                     // creation parameters
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//int WINAPI //WinMain    (HINSTANCE hInstance, HINSTANCE hPrevInstance,    PSTR szCmdLine, int iCmdShow)  
{
    
    add_globals(global_env);
    add_winglobals(global_env);
    apps.push_back(hInstance);
    MSG          msg;
    try {
        //auto path = std::filesystem::current_path(); //getting path
        std::filesystem::current_path("..\\example\\"); //setting path
        std::ifstream t("c13print1.lsp");
        //std::ifstream t("poormenu.lsp");
        //std::ifstream t("blokout.lsp");
        //std::ifstream t("environ.lsp");
        /*std::ifstream t("btnlook.lsp");*/
        //std::ifstream t("keyview.lsp");
        //std::ifstream t("helloworld.lsp");
        /*std::ifstream t("drawrect.lsp");*/
        /*std::ifstream t("gettextmetrics.lsp");*/
        /*std::ifstream t("lp2dp.lsp");*/
        /*std::ifstream t("mapmode.lsp");*/
        //std::ifstream t("sysmet1.lsp");
        //std::ifstream t("textout.lsp");
        std::stringstream buffer;
        buffer << t.rdbuf();
        run(buffer.str(), &global_env);
    }
    catch (std::string str) {
        ofstream myFile_Handler;
        myFile_Handler.open("log.txt", std::ios_base::app);
        myFile_Handler << str.c_str() << endl;
        myFile_Handler.close();
        exit(1);
    }
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#pragma warning(push, 0)
    return msg.wParam;
#pragma warning(pop)
}
cell proc_load(const cells& c) {
    std::string file(c[0].val);
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    run(buffer.str(), &global_env);
    return true_sym;
}