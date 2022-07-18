#include <windows.h>
#include <fstream>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"
HWND str_hwnd(std::string str) {
    DWORD64 n1(_atoi64(str.c_str()));
    return (HWND)n1;
}
std::string hwnd_str(HWND  hwnd) {
    return std::to_string((DWORD64)hwnd);
}

HDC str_hdc(std::string str) {
    DWORD64 n1(_atoi64(str.c_str()));
    return (HDC)n1;
}
std::string hdc_str(HDC  hwnd) {
    return std::to_string((DWORD64)hwnd);
}

cell proc_drawtext(const cells& c);
cell proc_app(const cells& c);
cell proc_register(const cells& c);
cell proc_create1(const cells& c);
std::vector<HINSTANCE> apps;
std::vector<PAINTSTRUCT> pss;
environment global_env;
ATOM registerclass(HINSTANCE hInstance, std::string app);
HWND createwindow(HINSTANCE hInstance, std::string app);
cell proc_app(const cells& c) {
    return cell(Number, "0");
}
cell proc_quit(const cells& c) {
    PostQuitMessage(0);
    return true_sym;
}

cell proc_register(const cells& c) {
    long n(atol(c[0].val.c_str()));
    registerclass(apps[n], c[1].val.c_str());
    return cell(Number, "33");
}
cell proc_create1(const cells& c) {
    long n(atol(c[0].val.c_str()));
    HWND hwnd = createwindow(apps[n], c[1].val.c_str());
    ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);
    return cell(Number, "11");
}
cell proc_drawtext(const cells& c)
{
    //HDC dc;
    //long n(atol(c[0].val.c_str()));
    //long left(atol(c[2].val.c_str()));
    //long top(atol(c[3].val.c_str()));
    //long right(atol(c[4].val.c_str()));
    //long bottom(atol(c[5].val.c_str()));
    //std::string base(c[1].val.c_str());
    //RECT        rect;
    //rect.left = left;//10;
    //rect.top = top;//10;
    //rect.right = right;//200;
    //rect.bottom = bottom;//100;
    //DrawText(list[n], (LPCSTR)(base.c_str()), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    //return cell(String, base);
    long n2(atol(c[0].list[0].val.c_str()));//ps
    std::string base(c[1].val.c_str());
    //HWND hwnd = hwnds[n0];
    //HDC         hdc = hdcs[n1]; //hdc
    HWND hwnd = str_hwnd(c[0].list[1].val);
    HDC         hdc = str_hdc(c[0].list[2].val);
    PAINTSTRUCT ps = pss[n2]; //ps    
    long left, top, right, bottom;
    if (c[2].type != List) {
        left = atol(c[2].val.c_str());
        top = (atol(c[3].val.c_str()));
        right = (atol(c[4].val.c_str()));
        bottom = (atol(c[5].val.c_str()));
    }
    else {
        left = atol(c[2].list[0].val.c_str());
        top = atol(c[2].list[1].val.c_str());
        right = atol(c[2].list[2].val.c_str());
        bottom = atol(c[2].list[3].val.c_str());
    }
    RECT        rect = {0};
    rect.left = left;//10;
    rect.top = top;//10;
    rect.right = right;//200;
    rect.bottom = bottom;//100;
    DrawText(hdc, (LPCSTR)(base.c_str()), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);    
    return true_sym;
}
cell proc_line(const cells& c)
{
    long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = hwnds[n0];
    //HDC         hdc = hdcs[n1]; //hdc
    HWND hwnd = str_hwnd(c[0].list[1].val);
    HDC         hdc = str_hdc(c[0].list[2].val);
    PAINTSTRUCT ps = pss[n2]; //ps    
    long left(atol(c[1].val.c_str()));
    long top(atol(c[2].val.c_str()));
    long right(atol(c[3].val.c_str()));
    long bottom(atol(c[4].val.c_str()));
    MoveToEx(hdc, left, top, NULL);
    LineTo(hdc, right, bottom);
    return true_sym;
}
void onpaint(HWND hwnd);

cell proc_getclientrect(const cells& c) {
    RECT        rect;
    DWORD64 n1(_atoi64(c[0].val.c_str()));
    HWND hw = (HWND)n1;
    HWND hwnd = hw;
    //HWND hwnd = hwnds[n0];
    GetClientRect(hwnd, &rect);
    std::ostringstream stream;
    stream << "(list " << rect.left << " " <<rect.top << " " << rect.right << " "<< rect.bottom << " " << " )";
    return run(stream.str(), &global_env);
}

cell proc_beginpaint(const cells& c) {
    HWND hwnd = str_hwnd(c[0].val);
    HDC         hdc;
    PAINTSTRUCT ps;
    //RECT        rect;
    std::ostringstream stringStream;
    
    hdc = BeginPaint(hwnd, &ps);
    
    pss.push_back(ps);    
    std::ostringstream stream;
    stream << "(list " <<pss.size()-1<< " "<< hwnd_str(hwnd) << " " << hdc_str(hdc) << " )";
    return run(stream.str(), &global_env);
}
cell proc_endpaint(const cells& c) {

    long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = hwnds[n0]; 
    HWND hwnd = str_hwnd(c[0].list[1].val);        
    PAINTSTRUCT ps = pss[n2]; //ps    
    EndPaint(hwnd, &ps);
    pss.pop_back();
    return true_sym;
}


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

void onpaint(HWND hwnd);
bool haserror=false;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    //char buff[100];
    long hwndindex;
    cell a;
    std::string str;
    //if (message == WM_PAINT || WM_CREATE == message)return 0;
    if(!haserror)
    try {
        
#pragma warning(push, 0)
        
#pragma warning(pop)
        str = "(winproc  ";
        str += hwnd_str(hwnd);
        str += " ";
        str += std::to_string(message);        
        str += ")";
        a = run(str, &global_env);
        HWND hw = (HWND)((DWORD64)hwnd);
        if (message == WM_PAINT || message == WM_DESTROY) {
            return 0;
        }
    }
    catch (std::string msg) {
        //MessageBox(hwnd, msg.c_str(), "error", 0);
        //return DefWindowProc(hwnd, message, wParam, lParam);
        haserror = true;
    }else
    
    switch (message)
    {
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
        CW_USEDEFAULT,              // initial x position
        CW_USEDEFAULT,              // initial y position
        CW_USEDEFAULT,              // initial x size
        CW_USEDEFAULT,              // initial y size
        NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL);                     // creation parameters
}
void add_winglobals() {
    global_env["drawtext"] = cell(&proc_drawtext);
    global_env["app"] = cell(&proc_app);
    global_env["register"] = cell(&proc_register);
    global_env["create"] = cell(&proc_create1);
    global_env["beginpaint"] = cell(&proc_beginpaint);
    global_env["endpaint"] = cell(&proc_endpaint);
    global_env["drawtext"] = cell(&proc_drawtext);
    global_env["line"] = cell(&proc_line);
    global_env["getclientrect"] = cell(&proc_getclientrect);
    global_env["quit"] = cell(&proc_quit);    
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//int WINAPI //WinMain    (HINSTANCE hInstance, HINSTANCE hPrevInstance,    PSTR szCmdLine, int iCmdShow)  
{
    
    add_globals(global_env);
    add_winglobals();
    //environment env = global_env;
    
    apps.push_back(hInstance);
    //HWND         hwnd;
    MSG          msg;
    std::ifstream t("main.lsp");
    std::stringstream buffer;
    buffer << t.rdbuf();
    run(buffer.str(), &global_env);
    /*std::string a="1";
    a +=  "2";
    a += "3";
    run("(define winproc (lambda (hwnd msg wp lp)(paint1 hwnd msg '123rtya°¡»òÕßµ¼ÖÂversion1.1' 2 )))", &global_env);
    run("(register (app) 'HelloWin1' 'winproc')", &global_env);
    run("(create (app) 'HelloWin1')", &global_env);*/
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#pragma warning(push, 0)
    return msg.wParam;
#pragma warning(pop)
}



