#include <windows.h>
#include <fstream>
#include <filesystem>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"
#include "listview.h"
void Rectangle1(HDC hdc, int l, int t, int r, int b) {
    MoveToEx(hdc, l, t, NULL);
    LineTo(hdc, l, b);
    LineTo(hdc, r, b);
    LineTo(hdc, r, t);
    LineTo(hdc, l, t);
}
HMENU para_tohmenu(const cell c) {
    return (HMENU)atoll(c.val.c_str());
}
void rect_xor(HWND hwnd, POINT ptBeg, POINT ptEnd)
{
    HDC hdc;

    hdc = GetDC(hwnd);
    // int oldROP = GetROP2;
    // SetROP2(oldROP);
    SetROP2(hdc, R2_NOT);
    //SelectObject (hdc, GetStockObject (NULL_BRUSH)) ;
    Rectangle1(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

    ReleaseDC(hwnd, hdc);
}
POINT para_getpoint(const cell& c) {
    POINT r;
    r.x = atol(c.list[0].val.c_str());
    r.y = atol(c.list[1].val.c_str());
    return r;
}
void para_getrect(const cells& c, int base, RECT& rect) {
    long left, top, right, bottom;
    if (c[base].type != List) {
        left = atol(c[base].val.c_str());
        top = (atol(c[base + 1].val.c_str()));
        right = (atol(c[base + 2].val.c_str()));
        bottom = (atol(c[base + 3].val.c_str()));
    }
    else {
        left = atol(c[base].list[0].val.c_str());
        top = atol(c[base].list[1].val.c_str());
        right = atol(c[base].list[2].val.c_str());
        bottom = atol(c[base].list[3].val.c_str());
    }
    rect.left = left;//10;
    rect.top = top;//10;
    rect.right = right;//200;
    rect.bottom = bottom;//100;
}

PAINTSTRUCT* para_str_ps(std::string str) {
    UINT64 n1(strtoull(str.c_str(), NULL, 0));
    PAINTSTRUCT* pp = (PAINTSTRUCT*)((void*)n1);
    return pp;
}
void para_str_ps_r(std::string str, PAINTSTRUCT& ps) {
    UINT64 n1(strtoull(str.c_str(), NULL, 0));
    ps = *((PAINTSTRUCT*)((void*)n1));    
}
std::string para_ps_str(PAINTSTRUCT* p) {
    UINT64 a = (UINT64)((void*)p);
    std::ostringstream os;
    os << "'";
    os << a;
    os << "'";
    return os.str();
}

HWND para_str_hwnd(std::string str) {
    DWORD64 n1(_atoi64(str.c_str()));
    return (HWND)n1;
}
std::string para_hwnd_str(HWND  hwnd) {
    return std::to_string((DWORD64)hwnd);
}

HDC para_str_hdc(std::string str) {
    UINT64 n1(strtoull(str.c_str(), NULL, 0));
    return (HDC)n1;
}
std::string para_hdc_str(HDC  hwnd) {
    std::ostringstream os;
    os << "'";
    os << (UINT64)hwnd;
    os << "'";
    return os.str();
    //return std::to_string((UINT64)hwnd);
}
void para_gettriple(const cells& c, int base, HWND& hwnd, HDC& hdc, PAINTSTRUCT& ps) {
    hwnd = para_str_hwnd(c[base].list[0].val);
    hdc = para_str_hdc(c[base].list[2].val);
    para_str_ps_r(c[base].list[1].val,ps);
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
cell proc_GetKeyNameText(const cells& c) {
    LONG l = atol(c[0].val.c_str());    
    TCHAR        szKeyName[32];
    GetKeyNameText(l, szKeyName,sizeof(szKeyName) / sizeof(TCHAR));
    cell result(String,szKeyName);
    return result;
}
cell proc_gettextmetrics(const cells& c) {
    HWND hwnd = para_str_hwnd(c[0].val);
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
cell proc_getsystemmetrics(const cells& c) {
    long n = atoi(eval(c[0],&global_env).val.c_str());
    long k = GetSystemMetrics(n);
    cell result(String,std::to_string(k));    
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
    HDC         hdc = para_str_hdc(c[0].val);
    RECT        rect = { 0 };
    para_getrect(c, 2, rect);
    DrawText(hdc, (LPCSTR)(base.c_str()), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);    
    return true_sym;
}
cell proc_textout(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    std::string base(c[3].val.c_str()); 
    HDC         hdc = para_str_hdc(c[0].val);
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
cell proc_lv_create(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);    
    long base = 1;
    RECT        rect = { 0 };
    para_getrect(c, 1, rect);
    HWND hList = CreateListView(hwnd, 101, rect);    
    cell result(String, para_hwnd_str(hList));
    return result;
}
cell proc_lv_setcolumns(const cells& c)
{
    HWND hList = para_str_hwnd(c[0].val);    
    LVCOLUMN  LvCol;
    memset(&LvCol, 0, sizeof(LvCol));
    LvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    for (int i = 0; i < c[1].list.size(); i++) {
        LvCol.cx = atoi(c[2].list[i].val.c_str());
        std::string c1 = c[1].list[i].val;
        LvCol.pszText = (LPSTR)c1.c_str();
        SendMessage(hList, LVM_INSERTCOLUMN, i, (LPARAM)&LvCol);
    }    
    return true_sym;
}
int kk = 0;
cell proc_lv_appenditem(const cells& c)
{
    HWND hList = para_str_hwnd(c[0].val);
    LVITEM LvItem;    
    memset(&LvItem, 0, sizeof(LvItem)); // Zero struct's Members    
    LvItem.mask = LVIF_TEXT;   // Text Style
    LvItem.cchTextMax = 256; // Max size of test
    int index = (int)SendMessage(hList, LVM_GETITEMCOUNT, 0, 0);//atoi(c[1].val.c_str());          // choose item  
    LvItem.iItem = index;
    LvItem.iSubItem = 0;       // Put in first coluom
    int base = 2;
    LvItem.pszText =(LPSTR)(c[base].list[0].val.c_str());
    SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&LvItem); // Send info to the Listview

    for (int i = 1; i < c[base].list.size(); i++) // Add SubItems in a loop
    {
        LvItem.iSubItem = i;        
        LvItem.pszText = (LPSTR)(c[base].list[i].val.c_str());
        SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&LvItem); // Enter text to SubItems
    }    
    return true_sym;
}

cell proc_loword(const cells& c) {
    WPARAM wp = atol(c[0].val.c_str());
    cell r(Number, std::to_string(LOWORD(wp)));
    return r;
}
cell proc_hiword(const cells& c) {
    WPARAM wp = atol(c[0].val.c_str());
    cell r(Number, std::to_string(HIWORD(wp)));
    return r;
}

cell proc_createbutton(const cells& c)
{    
    HWND hwnd = para_str_hwnd(c[0].val);
    DWORD iStyle = atol(c[1].val.c_str());
    RECT rect = {0};
    para_getrect(c, 4, rect);
    HMENU id = para_tohmenu(c[2]);
    std::string title = c[3].val;
    HWND hwndButton = CreateWindow(TEXT("button"),
        title.c_str(),
        WS_CHILD | WS_VISIBLE | iStyle,
        rect.left,rect.top,rect.right,rect.bottom,
        hwnd, id,
        0, NULL);
    cell r(String, para_hwnd_str(hwndButton));
    return r;
}
cell proc_ls_getsel(const cells& c)
{
    int          iIndex, iLength;
    TCHAR* pVarName, * pVarValue;

    HWND hwndList = para_str_hwnd(c[0].val);
    iIndex = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
    iLength = (int)SendMessage(hwndList, LB_GETTEXTLEN, iIndex, 0) + 1;
    pVarName = (TCHAR*)calloc(iLength, sizeof(TCHAR));
    SendMessage(hwndList, LB_GETTEXT, iIndex, (LPARAM)pVarName);

    // Get environment string.

    iLength = GetEnvironmentVariable(pVarName, NULL, 0);
    pVarValue =(TCHAR*) calloc(iLength, sizeof(TCHAR));
    GetEnvironmentVariable(pVarName, pVarValue, iLength);

    std::string str(pVarValue);
    free(pVarName);
    free(pVarValue);
    cell r(String, str);
    return r;
}
cell proc_ls_add(const cells& c)
{
    HWND hwndList = para_str_hwnd(c[0].val);
    TCHAR* pVarName = (TCHAR*)c[1].val.c_str();
    SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVarName);
    return true_sym;
}
cell proc_GetEnvironmentStrings(const cells& c)
{
    cell r(List);
    int     iLength;
    TCHAR* pVarBlock, * pVarBeg, * pVarEnd, * pVarName, * pVarBlockHead;

    pVarBlockHead = pVarBlock = GetEnvironmentStrings();  // Get pointer to environment block

    while (*pVarBlock)
    {
        if (*pVarBlock != '=')   // Skip variable names beginning with '='
        {
            pVarBeg = pVarBlock;              // Beginning of variable name
            while (*pVarBlock++ != '=');      // Scan until '='
            pVarEnd = pVarBlock - 1;          // Points to '=' sign
            iLength = (int)(pVarEnd - pVarBeg);      // Length of variable name

                 // Allocate memory for the variable name and terminating
                 // zero. Copy the variable name and append a zero.

            pVarName = (TCHAR*)calloc(iLength + 1, sizeof(TCHAR));
            CopyMemory(pVarName, pVarBeg, iLength * sizeof(TCHAR));
            pVarName[iLength] = '\0';

            // Put the variable name in the list box and free memory.
            std::string str(pVarName);
            cell r1(String, str);
            r.list.push_back(r1);
            free(pVarName);
        }
        while (*pVarBlock++ != '\0');     // Scan until terminating zero
    }
    FreeEnvironmentStrings(pVarBlockHead);
    
    return r;
}

cell proc_createlistbox(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
    DWORD iStyle = atol(c[1].val.c_str());
    RECT rect = { 0 };
    para_getrect(c, 4, rect);
    HMENU id = para_tohmenu(c[2]);//(HMENU)atoll(c[2].val.c_str());
    std::string title = c[3].val;
    HWND hList = CreateWindow(TEXT("listbox"),
        NULL,
        WS_CHILD | WS_VISIBLE | LBS_STANDARD,
        rect.left, rect.top, rect.right, rect.bottom,
        hwnd, id,
        0, NULL);
    //FillListBox(hList);
    cell r(String, para_hwnd_str(hList));
    return r;
}
cell proc_createstatic(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
    DWORD iStyle = atol(c[1].val.c_str());
    RECT rect = { 0 };
    para_getrect(c, 4, rect);
    HMENU id = para_tohmenu(c[2]);
    std::string title = c[3].val;
    HWND hwndButton = CreateWindow(TEXT("static"),
        NULL,
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        rect.left, rect.top, rect.right, rect.bottom,
        hwnd, id,
        0, NULL);
    cell r(String, para_hwnd_str(hwndButton));
    return r;
}
cell proc_setwindowtext(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
    std::string str;
    if (c[1].type == List)
        str = to_string1(c[1].list);
    else
        str = c[1].val;
    SetWindowText(hwnd, str.c_str());
    return true_sym;
}
cell proc_tostring(const cells& c)
{
    cell r(String, to_string1(c));
    return r;
}


cell proc_trap(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
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
    HDC         hdc = para_str_hdc(c[0].val);
    long mode = atol(c[1].val.c_str());
    SetMapMode(hdc,mode);
    return true_sym;
}
cell proc_setwindowextent(const cells& c)
{
    //long n2(atol(c[0].list[0].val.c_str()));//ps
    //HWND hwnd = str_hwnd(c[0].list[1].val);
    //HDC         hdc = str_hdc(c[0].list[2].val);
    HDC         hdc = para_str_hdc(c[0].val);
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
    HDC         hdc = para_str_hdc(c[0].val);
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
    HDC         hdc = para_str_hdc(c[0].val);
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
    HDC         hdc = para_str_hdc(c[0].val);
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
    HWND hwnd = para_str_hwnd(c[0].val);
    HDC         hdc;
  
    hdc = BeginPaint(hwnd, &ps);

    std::ostringstream stringStream;
    UINT64 a = (UINT64)((void*)&ps);
    PAINTSTRUCT* qq = &ps;
    PAINTSTRUCT* pp = (PAINTSTRUCT*)((void*)a);    
    std::ostringstream stream;
    stream << "(list 0 "  << " " << para_hwnd_str(hwnd) << " " << para_hdc_str(hdc) << " " << para_ps_str(&ps) << ")";
    return run(stream.str(), &global_env);
}
cell proc_endpaint(const cells& c) {

    long n2(atol(c[0].list[0].val.c_str()));//ps
    HWND hwnd = para_str_hwnd(c[0].list[1].val);        
    PAINTSTRUCT* ps1 = para_str_ps(c[0].list[3].val);

    

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
cell proc_invalidaterect(const cells& c){
    HWND hwnd = para_str_hwnd(c[0].val);
    InvalidateRect(hwnd, NULL, TRUE);
    return true_sym;
}
cell proc_rect_xor(const cells& c) {
    HWND hwnd = para_str_hwnd(c[0].val);
    POINT p1 = para_getpoint(c[1]);
    POINT p2 = para_getpoint(c[2]);
    rect_xor(hwnd, p1, p2);
    return true_sym;
}

cell proc_rect1(const cells& c)
{
    HDC hdc = para_str_hdc(c[0].val);
    POINT p1 = para_getpoint(c[1]);
    POINT p2 = para_getpoint(c[2]);
    Rectangle1(hdc, p1.x, p1.y, p2.x, p2.y);
    return true_sym;
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
    
    switch (message)
    {
        case WM_CREATE:        
            return 0;       
        //case WM_CHAR:
        //    proc_char1(hwnd,wParam);
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
    /*global_env["mouseup1"] = cell(&proc_up_wrap);
    global_env["mousedown1"] = cell(&proc_down_wrap);
    global_env["mousemove1"] = cell(&proc_move_wrap);
    global_env["paint1"] = cell(&proc_paint_wrap)*/;
    //global_env["char1"] = cell(&proc_char1_wrap);
    global_env["tostring"] = cell(&proc_tostring);
    global_env["invalidaterect"] = cell(&proc_invalidaterect);
    global_env["rect_xor"] = cell(&proc_rect_xor);
    global_env["rect1"] = cell(&proc_rect1);
    
       
}
#include "listview.h"

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
        std::ifstream t("blokout.lsp");
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