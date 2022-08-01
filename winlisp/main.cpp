#include <windows.h>
#include <fstream>
#include <filesystem>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"



PAINTSTRUCT* str_ps(std::string str) {
    UINT64 n1(strtoull(str.c_str(), NULL, 0));
    PAINTSTRUCT* pp = (PAINTSTRUCT*)((void*)n1);
    return pp;
}
std::string ps_str(PAINTSTRUCT* p) {
    UINT64 a = (UINT64)((void*)p);
    std::ostringstream os;
    os << "'";
    os << a;
    os << "'";
    return os.str();
}

HWND str_hwnd(std::string str) {
    DWORD64 n1(_atoi64(str.c_str()));
    return (HWND)n1;
}
std::string hwnd_str(HWND  hwnd) {
    return std::to_string((DWORD64)hwnd);
}

HDC str_hdc(std::string str) {
    UINT64 n1(strtoull(str.c_str(), NULL, 0));
    return (HDC)n1;
}
std::string hdc_str(HDC  hwnd) {
    std::ostringstream os;
    os << "'";
    os << (UINT64)hwnd;
    os << "'";
    return os.str();
    //return std::to_string((UINT64)hwnd);
}
cell proc_load(const cells& c);
cell proc_drawtext(const cells& c);
cell proc_app(const cells& c);
cell proc_register(const cells& c);
cell proc_create1(const cells& c);
std::vector<HINSTANCE> apps;
//std::vector<PAINTSTRUCT> pss;
environment global_env;
ATOM registerclass(HINSTANCE hInstance, std::string app);
HWND createwindow(HINSTANCE hInstance, std::string app);
typedef struct tagtriple {
    int  cxChar, cyChar, cxCaps;
} triple;
triple gettextmetrics(HWND hwnd) {
    triple t;
    HDC         hdc;
    TEXTMETRIC  tm;
    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    t.cxChar = tm.tmAveCharWidth;
    t.cyChar = tm.tmHeight + tm.tmExternalLeading;
    t.cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * t.cxChar / 2;
    ReleaseDC(hwnd, hdc);
    return t;
}
cell proc_gettextmetrics(const cells& c) {
    HWND hwnd = str_hwnd(c[0].val);
    cell result(List);
    triple t = gettextmetrics(hwnd);
    cell c1(Number,std::to_string(t.cxChar));
    result.list.push_back(c1);
    cell c2(Number, std::to_string(t.cyChar));
    result.list.push_back(c2);
    cell c3(Number, std::to_string(t.cxCaps));
    result.list.push_back(c3);
    return result;
}

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
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    std::string base(c[1].val.c_str());
    //HWND hwnd = hwnds[n0];
    //HDC         hdc = hdcs[n1]; //hdc
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    //PAINTSTRUCT ps = pss[n2]; //ps    
    HDC         hdc = str_hdc(c[0].val);
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
cell proc_textout(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    std::string base(c[3].val.c_str()); 
    HDC         hdc = str_hdc(c[0].val);
    long left, top;
    if (c[2].type != List) {
        left = atol(c[1].val.c_str());
        top = (atol(c[2].val.c_str()));
    }
    else {
        left = atol(c[1].list[0].val.c_str());
        top = atol(c[1].list[1].val.c_str());
    }
    TextOut(hdc, left,top, (LPCSTR)(base.c_str()),
        (int)base.size());
    return true_sym;
}
cell proc_setwindowtext(const cells& c)
{
    HWND hwnd = str_hwnd(c[0].val);
    std::string str;
    if (c[1].type == List)
        str = to_string1(c[1].list);
    else
        str = c[1].val;
    SetWindowText(hwnd, str.c_str());
    return true_sym;
}
cell proc_trap(const cells& c)
{
    HWND hwnd = str_hwnd(c[0].val);
    std::string str= c[1].val;
    str = eval(c[1], &global_env).val;
    SetWindowText(hwnd, str.c_str());
    return true_sym;
}
cell proc_eval(const cells& c)
{
    //HWND hwnd = str_hwnd(c[0].val);
    //std::string str = c[1].val;
    //str = eval(c[1], &global_env).val;
    //SetWindowText(hwnd, str.c_str());
    return eval(c[0], &global_env);
}
cell proc_setmapmode(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    HDC         hdc = str_hdc(c[0].val);
    long mode = atol(c[1].val.c_str());
    SetMapMode(hdc,mode);
    return true_sym;
}
cell proc_setwindowextent(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    HDC         hdc = str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetWindowExtEx(hdc, x, y, NULL);
    return true_sym;
}
cell proc_setviewextent(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    HDC         hdc = str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetViewportExtEx(hdc, x, y, NULL);
    return true_sym;
}
cell proc_line(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = hwnds[n0];
    //HDC         hdc = hdcs[n1]; //hdc
/*    HWND hwnd = str_hwnd(c[0].list[1].val);
    HDC         hdc = str_hdc(c[0].list[2].val); */  
    HDC         hdc = str_hdc(c[0].val);
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
    //long mapmode(atol(c[1].val.c_str()));
    //long left(atol(c[1].val.c_str()));
    //long top(atol(c[2].val.c_str()));
    //long right(atol(c[3].val.c_str()));
    //long bottom(atol(c[4].val.c_str()));
    std::ostringstream stream;
    stream << "(list " << rect.left << " " <<rect.top << " " << rect.right << " "<< rect.bottom << " " << " )";
    return run(stream.str(), &global_env);
}
//(def rect(lr2dr hdc mapmode rect))
cell proc_lr2dr(const cells& c) {
    //RECT        rect;
    //DWORD64 n1(_atoi64(c[0].val.c_str()));
    //HWND hw = (HWND)n1;
    //HWND hwnd = hw;
    //HWND hwnd = hwnds[n0];
    //GetClientRect(hwnd, &rect);
    HDC         hdc = str_hdc(c[0].val);
    long mapmode = atol(c[1].val.c_str()); 
    long left = atol(c[2].list[0].val.c_str());
    long top = atol(c[2].list[1].val.c_str());
    long right = atol(c[2].list[2].val.c_str());
    long bottom = atol(c[2].list[3].val.c_str());

    RECT        rect = { 0 };
    rect.left = left;//10;
    rect.top = top;//10;
    rect.right = right;//200;
    rect.bottom = bottom;//100;
    SaveDC(hdc);
    SetMapMode(hdc, mapmode);
    DPtoLP(hdc, (PPOINT)&rect, 2);
    RestoreDC(hdc, -1);
    std::ostringstream stream;
    stream << "(list " << rect.left << " " << rect.top << " " << rect.right << " " << rect.bottom << " " << " )";
    return run(stream.str(), &global_env);
}
PAINTSTRUCT ps;
cell proc_beginpaint(const cells& c) {
    HWND hwnd = str_hwnd(c[0].val);
    HDC         hdc;
    
    //RECT        rect;
    std::ostringstream stringStream;
    
    hdc = BeginPaint(hwnd, &ps);
    UINT64 a = (UINT64)((void*)&ps);
    PAINTSTRUCT* qq = &ps;
    PAINTSTRUCT* pp = (PAINTSTRUCT*)((void*)a);    
    std::ostringstream stream;
    stream << "(list 0 "  << " " << hwnd_str(hwnd) << " " << hdc_str(hdc) << " " << ps_str(&ps) << ")";
    return run(stream.str(), &global_env);
}
cell proc_endpaint(const cells& c) {

    long n2(atol(c[0].list[0].val.c_str()));//ps
    HWND hwnd = str_hwnd(c[0].list[1].val);        
    PAINTSTRUCT* ps1 = str_ps(c[0].list[3].val);
    EndPaint(hwnd, ps1);
    //pss.pop_back();
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
        //SetWindowText(hwnd, msg.c_str());
        ofstream myFile_Handler;
        myFile_Handler.open("log.txt", std::ios_base::app);
        myFile_Handler << msg << endl;
        myFile_Handler.close();
        exit(2);
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
    global_env["load"] = cell(&proc_load);
    global_env["textout"] = cell(&proc_textout);
    global_env["setmapmode"] = cell(&proc_setmapmode);
    global_env["setwindowextent"] = cell(&proc_setwindowextent);
    global_env["setviewextent"] = cell(&proc_setviewextent);
    global_env["setwindowtext"] = cell(&proc_setwindowtext);
    global_env["lr2dr"] = cell(&proc_lr2dr);
    global_env["trap"] = cell(&proc_trap);
    global_env["eval"] = cell(&proc_eval);
    global_env["gettextmetrics"] = cell(&proc_gettextmetrics);
    
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//int WINAPI //WinMain    (HINSTANCE hInstance, HINSTANCE hPrevInstance,    PSTR szCmdLine, int iCmdShow)  
{
    
    add_globals(global_env);
    add_winglobals();
    apps.push_back(hInstance);
    MSG          msg;
    try {
        //auto path = std::filesystem::current_path(); //getting path
        std::filesystem::current_path("..\\example\\"); //setting path
        std::ifstream t("gettextmetrics.lsp");
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



