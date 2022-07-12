#include <windows.h>
#include <fstream>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"
cell proc_drawtext(const cells& c);
cell proc_app(const cells& c);
cell proc_register(const cells& c);
cell proc_create1(const cells& c);
cell proc_paint1(const cells& c);
std::vector<HDC> list;
std::vector<HINSTANCE> apps;
std::vector<HWND> hwnds;
std::vector<HDC> hdcs;
std::vector<PAINTSTRUCT> pss;
environment global_env;
ATOM registerclass(HINSTANCE hInstance, std::string app);
HWND createwindow(HINSTANCE hInstance, std::string app);
cell proc_app(const cells& c) {
    return cell(Number, "0");
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
    long n0(atol(c[0].list[0].val.c_str()));//hwnd
    long n1(atol(c[0].list[1].val.c_str()));//hdc
    long n2(atol(c[0].list[2].val.c_str()));//ps
    std::string base(c[1].val.c_str());
    HWND hwnd = hwnds[n0];
    HDC         hdc = hdcs[n1]; //hdc
    PAINTSTRUCT ps = pss[n2]; //ps    
    long left(atol(c[2].val.c_str()));
    long top(atol(c[3].val.c_str()));
    long right(atol(c[4].val.c_str()));
    long bottom(atol(c[5].val.c_str()));    
    RECT        rect;
    rect.left = left;//10;
    rect.top = top;//10;
    rect.right = right;//200;
    rect.bottom = bottom;//100;
    DrawText(hdc, (LPCSTR)(base.c_str()), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);    
    return true_sym;
}
cell proc_line(const cells& c)
{
    long n0(atol(c[0].list[0].val.c_str()));//hwnd
    long n1(atol(c[0].list[1].val.c_str()));//hdc
    long n2(atol(c[0].list[2].val.c_str()));//ps
    HWND hwnd = hwnds[n0];
    HDC         hdc = hdcs[n1]; //hdc
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
cell proc_paint1(const cells& c) {
    
    long n0(atol(c[0].val.c_str()));
    long n1(atol(c[1].val.c_str()));
    std::string str(c[2].val.c_str());
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;
    std::ostringstream stringStream;
    HWND hwnd = hwnds[n0];
    if (n1 == 15) {//WM_PAINT
        //onpaint_metrics(hwnd); return cell(Number, "0");
        //onpaint(hwnd); return cell(Number, "0");
        // for (paint str)
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        DrawText(hdc, str.c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
    }
    return cell(Number, "22");
}
cell proc_beginpaint(const cells& c) {

    long n0(atol(c[0].val.c_str()));
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;
    std::ostringstream stringStream;
    HWND hwnd = hwnds[n0];    
    hdc = BeginPaint(hwnd, &ps);
    hdcs.push_back(hdc);
    pss.push_back(ps);
    std::string str;
    str += "(list ";
    str += std::to_string(n0);
    str += " ";
    str += std::to_string(hdcs.size() - 1);
    str += " ";
    str += std::to_string(pss.size()-1);
    str += " )";    
    std::ostringstream stream;
    stream << "(list " <<n0<<" "<<hdcs.size()-1<<" "<<pss.size()-1<<" )";
    return run(stream.str(), &global_env);
}
cell proc_endpaint(const cells& c) {

    long n0(atol(c[0].list[0].val.c_str()));//hwnd
    long n1(atol(c[0].list[1].val.c_str()));//hdc
    long n2(atol(c[0].list[2].val.c_str()));//ps
    HWND hwnd = hwnds[n0]; 
    HDC         hdc = hdcs[n1]; //hdc
    PAINTSTRUCT ps = pss[n2]; //ps    
    EndPaint(hwnd, &ps);
    hdcs.pop_back();
    pss.pop_back();
    return true_sym;
}
void onpaint(HWND hwnd) {
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;
    std::ostringstream stringStream;
    hdc = BeginPaint(hwnd, &ps);
    list.push_back(hdc);
    GetClientRect(hwnd, &rect);
    stringStream << "(drawtext " << list.size() - 1 << " '12s汉字大众化'" << " " << rect.left << " " << rect.top << " " << rect.right << " " << rect.bottom << ")";
    eval(read(stringStream.str()), &global_env);
    list.pop_back();
    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM registerclass(HINSTANCE hInstance, std::string app) {
    //static TCHAR szAppName[] = TEXT("HelloWin");
    WNDCLASS     wndclass;
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
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    char buff[100];
    long hwndindex;
    cell a;
    std::string str;
    //if (message == WM_PAINT || WM_CREATE == message)return 0;
    switch (message)
    {
    case WM_PAINT:
        hwnds.push_back(hwnd);
        hwndindex = hwnds.size() - 1;
        str = "(winproc  ";
        str += std::to_string(hwndindex);
        str += " ";
        str += std::to_string(WM_PAINT);
        str += " 2 3 )";
        a = run(str, &global_env);
        hwnds.pop_back();
        return 0;
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
    global_env["paint1"] = cell(&proc_paint1);
    global_env["beginpaint"] = cell(&proc_beginpaint);
    global_env["endpaint"] = cell(&proc_endpaint);
    global_env["drawtext"] = cell(&proc_drawtext);
    global_env["line"] = cell(&proc_line);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    
    add_globals(global_env);
    add_winglobals();
    //environment env = global_env;
    
    apps.push_back(hInstance);
    HWND         hwnd;
    MSG          msg;
    std::ifstream t("main.lsp");
    std::stringstream buffer;
    buffer << t.rdbuf();
    run(buffer.str(), &global_env);
    /*std::string a="1";
    a +=  "2";
    a += "3";
    run("(define winproc (lambda (hwnd msg wp lp)(paint1 hwnd msg '123rtya啊或者导致version1.1' 2 )))", &global_env);
    run("(register (app) 'HelloWin1' 'winproc')", &global_env);
    run("(create (app) 'HelloWin1')", &global_env);*/
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}



