#include <windows.h>
#include <fstream>
#include <filesystem>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"
#include "listview.h"
#include "proc.h"

HINSTANCE ghInstance;
static TCHAR szAppName[] = TEXT("PoorMenu");
environment global_env;
PAINTSTRUCT ps;
std::vector<HINSTANCE> apps;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

void add_winglobals(environment& global_env) {
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
    global_env["getsystemmetrics"] = cell(&proc_getsystemmetrics);
    global_env["lv_create"] = cell(&proc_lv_create);
    global_env["lv_setcolumns"] = cell(&proc_lv_setcolumns);
    global_env["lv_appenditem"] = cell(&proc_lv_appenditem);
    global_env["GetKeyNameText"] = cell(&proc_GetKeyNameText);
    global_env["createbutton"] = cell(&proc_createbutton);
    global_env["loword"] = cell(&proc_loword);
    global_env["hiword"] = cell(&proc_hiword);
    global_env["createlistbox"] = cell(&proc_createlistbox);
    global_env["createstatic"] = cell(&proc_createstatic);
    global_env["ls_getsel"] = cell(&proc_ls_getsel);
    global_env["GetEnvironmentStrings"] = cell(&proc_GetEnvironmentStrings);
    global_env["ls_add"] = cell(&proc_ls_add);
    global_env["tostring"] = cell(&proc_tostring);
    global_env["invalidaterect"] = cell(&proc_invalidaterect);
    global_env["rect_xor"] = cell(&proc_rect_xor);
    global_env["rectangle"] = cell(&proc_rect1);
    global_env["getsystemmenu"] = cell(&proc_getsystemmenu);
    global_env["createmenu"] = cell(&proc_createmenu);
    global_env["setmenu"] = cell(&proc_setmenu);
    global_env["appendmenu"] = cell(&proc_appendmenu);
    global_env["moveto"] = cell(&proc_moveto);
    global_env["lineto"] = cell(&proc_lineto);
    global_env["savedc"] = cell(&proc_savedc);
    global_env["restoredc"] = cell(&proc_restoredc);
    global_env["setlogicalextent"] = cell(&proc_setlogicalextent);
    global_env["setdeviceextent"] = cell(&proc_setdeviceextent);
    global_env["setdeviceorigin"] = cell(&proc_setdeviceorigin);
    global_env["ellipse"] = cell(&proc_ellipse);

    global_env["getprinterdc"] = cell(&proc_getprinterdc);
    global_env["getdevicecaps"] = cell(&proc_getdevicecaps);
    global_env["startdoc"] = cell(&proc_startdoc);
    global_env["startpage"] = cell(&proc_startpage);
    global_env["endpage"] = cell(&proc_endpage);
    global_env["enddoc"] = cell(&proc_enddoc);
    global_env["deletedc"] = cell(&proc_deletedc);
    global_env["RegisterDialogClass"] = cell(&proc_RegisterDialogClass);
    global_env["CreateDialogBox"] = cell(&proc_CreateDialogBox);
    global_env["DestroyWindow"] = cell(&proc_DestroyWindow);
    global_env["DefWindowProc"] = cell(&proc_DefWindowProc);
    global_env["destroymenu"] = cell(&proc_destroymenu);
    global_env["MessageBox"] = cell(&proc_MessageBox);
}


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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    cell a;
    std::string str;    
    if(!haserror)
    try {
        
#pragma warning(push, 0)
        
#pragma warning(pop)
        char className[MAX_PATH];
        int res = GetClassName(hwnd, className, MAX_PATH);
        std::string winproc;
        if (res > 0) {
            std::string str(&className[0]);
            winproc = getwinproc(str);
        }
        if(winproc == "")
            winproc = "winproc";
        str = "(";
        str+= winproc;
        str += " ";
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


    }
    //LRESULT ra = DefWindowProc(hwnd, message, wParam, lParam);
    LRESULT ra = atoll(a.val.c_str());
    return ra;
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
        std::ifstream t("main.lsp");
        //std::ifstream t("poormenu2.lsp");
        //std::ifstream t("c11about1.lsp");        
        //std::ifstream t("hellonamedwinproc.lsp");
        //std::ifstream t("c13print1.lsp");
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
    ghInstance = hInstance;
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
