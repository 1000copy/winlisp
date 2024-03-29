#include "proc.h"
#include "lchar.h"
extern  environment global_env;
extern  PAINTSTRUCT ps;
extern std::vector<HINSTANCE> apps;
extern HINSTANCE ghInstance;
LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
void CreateDialogBox(HWND, std::string, std::string);
void RegisterDialogClass(HWND, std::string, std::string);

cell proc_moveto(const cells& c)
{
    HDC hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    MoveToEx(hdc, x, y,NULL);
    return true_sym;
}
cell proc_lineto(const cells& c)
{
    HDC hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    LineTo(hdc,x,y);
    return true_sym;
}


void Rectangle1(HDC hdc, int l, int t, int r, int b) {
    MoveToEx(hdc, l, t, NULL);
    LineTo(hdc, l, b);
    LineTo(hdc, r, b);
    LineTo(hdc, r, t);
    LineTo(hdc, l, t);
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
cell proc_invalidaterect(const cells& c) {
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
ATOM registerclass(HINSTANCE hInstance, std::string app);
HWND createwindow(HINSTANCE hInstance, std::string app);
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
    GetKeyNameText(l, szKeyName, sizeof(szKeyName) / sizeof(TCHAR));
    cell result(String, szKeyName);
    return result;
}
cell proc_gettextmetrics(const cells& c) {
    HWND hwnd = para_str_hwnd(c[0].val);
    cell result(List);
    triple t = gettextmetrics(hwnd);
    cell c1(Number, std::to_string(t.cxChar));
    result.list.push_back(c1);
    cell c2(Number, std::to_string(t.cyChar));
    result.list.push_back(c2);
    cell c3(Number, std::to_string(t.cxCaps));
    result.list.push_back(c3);
    return result;
}
cell proc_getsystemmetrics(const cells& c) {
    long n = atoi(eval(c[0], &global_env).val.c_str());
    long k = GetSystemMetrics(n);
    cell result(String, std::to_string(k));
    return result;
}
cell proc_app(const cells& c) {
    return cell(Number, "0");
}
cell proc_quit(const cells& c) {
    PostQuitMessage(0);
    return true_sym;
}
std::map<std::string, std::string > map_of_winproc;
std::string getwinproc(std::string classname) {
    return map_of_winproc[classname];
}
std::map<std::string, std::string > map_of_dialogproc;
std::string getdialogproc(std::string classname) {
    return map_of_dialogproc[classname];
}
void setdialogproc(std::string classname, std::string dialogproc ) {
    map_of_dialogproc[classname] = dialogproc;
}

cell proc_register(const cells& c) {
    long n(atol(c[0].val.c_str()));
    registerclass(apps[n], c[1].val.c_str());
    if(c.size() >= 3)
        map_of_winproc[c[1].val] = c[2].val;
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
    std::string base(c[1].val.c_str());
    HDC         hdc = para_str_hdc(c[0].val);
    RECT        rect = { 0 };
    para_getrect(c, 2, rect);
    DrawText(hdc, (LPCSTR)(base.c_str()), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    return true_sym;
}
cell proc_textout(const cells& c)
{
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
    TextOut(hdc, left, top, (LPCSTR)(base.c_str()),
        (int)base.size());
    return true_sym;
}
cell proc_lv_create(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
    long base = 1;    
    

    RECT        rect = { 0 };
    para_getrect(c, 1, rect);
    HWND hList = CreateListView(hwnd, (HMENU)101, rect);
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
        LvCol.pszText = (__STR)c1.c_str();
        SendMessage(hList, LVM_INSERTCOLUMN, i, (LPARAM)&LvCol);
    }
    return true_sym;
}

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
    LvItem.pszText = (LPSTR)(c[base].list[0].val.c_str());
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
    RECT rect = { 0 };
    para_getrect(c, 4, rect);
    HMENU id = para_tohmenu(c[2]);
    std::string title = c[3].val;
    HWND hwndButton = CreateWindow(TEXT("button"),
        title.c_str(),
        WS_CHILD | WS_VISIBLE | iStyle,
        rect.left, rect.top, rect.right, rect.bottom,
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
    pVarValue = (TCHAR*)calloc(iLength, sizeof(TCHAR));
    GetEnvironmentVariable(pVarName, pVarValue, iLength);
    if (pVarValue == NULL) {
        return NULL;
    }
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
    std::string str = c[1].val;
    str = eval(c[1], &global_env).val;
    SetWindowText(hwnd, str.c_str());
    return true_sym;
}
cell proc_getsystemmenu(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
    cell r(String, std::to_string((LONG64)GetSystemMenu(hwnd, false)));
    return r;
}
cell proc_createmenu(const cells& c)
{
    HMENU h = CreateMenu();
    cell r(String, std::to_string((LONG64)h));
    return r;
}
cell proc_setmenu(const cells& c)
{
    HWND hwnd = para_str_hwnd(c[0].val);
    HMENU handle = para_tohmenu(c[1]);
    SetMenu(hwnd, handle);    
    return true_sym;
}

cell proc_appendmenu(const cells& c)
{
    HMENU handle = para_tohmenu(c[0]);
    LONG  style= atol(c[1].val.c_str());
    LONG  id = atol(c[2].val.c_str());
    std::string str (c[3].val);
    AppendMenu(handle, style, id, str.c_str());
    //cell r(String, std::to_string((LONG64)GetSystemMenu(hwnd, false)));
    return true_sym;
}
cell proc_eval(const cells& c)
{
    return eval(c[0], &global_env);
}
cell proc_setmapmode(const cells& c)
{
    HDC         hdc = para_str_hdc(c[0].val);
    long mode = atol(c[1].val.c_str());
    SetMapMode(hdc, mode);
    return true_sym;
}
cell proc_setwindowextent(const cells& c)
{
    HDC         hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetWindowExtEx(hdc, x, y, NULL);
    return true_sym;
}
cell proc_setviewextent(const cells& c)
{
    HDC         hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetViewportExtEx(hdc, x, y, NULL);
    return true_sym;
}
cell proc_line(const cells& c)
{
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
    GetClientRect(hwnd, &rect);
    std::ostringstream stream;
    stream << "(list " << rect.left << " " << rect.top << " " << rect.right << " " << rect.bottom << " " << " )";
    return run(stream.str(), &global_env);
}
//(def rect(lr2dr hdc mapmode rect))
cell proc_lr2dr(const cells& c) {
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
cell proc_beginpaint(const cells& c) {
    HWND hwnd = para_str_hwnd(c[0].val);
    HDC         hdc;

    hdc = BeginPaint(hwnd, &ps);

    std::ostringstream stringStream;
    UINT64 a = (UINT64)((void*)&ps);
    PAINTSTRUCT* qq = &ps;
    PAINTSTRUCT* pp = (PAINTSTRUCT*)((void*)a);
    std::ostringstream stream;
    stream << "(list 0 " << " " << para_hwnd_str(hwnd) << " " << para_hdc_str(hdc) << " " << para_ps_str(&ps) << ")";
    return run(stream.str(), &global_env);
}
cell proc_endpaint(const cells& c) {

    long n2(atol(c[0].list[0].val.c_str()));//ps
    HWND hwnd = para_str_hwnd(c[0].list[1].val);
    PAINTSTRUCT* ps1 = para_str_ps(c[0].list[3].val);
    EndPaint(hwnd, ps1);
    return true_sym;
}
cell proc_savedc(const cells& c){
    HDC         hdc = para_str_hdc(c[0].val);
    SaveDC(hdc);
    return true_sym;
}
cell proc_restoredc(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    RestoreDC(hdc, -1);
    return true_sym;
}
cell proc_setlogicalextent(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetWindowExtEx(hdc, x,y, NULL);
    return true_sym;
}
cell proc_setdeviceextent(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetViewportExtEx(hdc, x, y, NULL);
    return true_sym;
}
cell proc_setdeviceorigin(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    long x = atol(c[1].val.c_str());
    long y = atol(c[2].val.c_str());
    SetViewportOrgEx(hdc, x, y, NULL);
    return true_sym;
}
cell proc_ellipse(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    long a = atol(c[1].val.c_str());
    long b = atol(c[2].val.c_str());
    long cc = atol(c[3].val.c_str());
    long d = atol(c[4].val.c_str());
    Ellipse(hdc, a, b, cc, d);
    return true_sym;
}
HDC GetPrinterDC1(void)
{
    DWORD            dwNeeded, dwReturned;
    HDC              hdc;
    PRINTER_INFO_4* pinfo4;
    //PRINTER_INFO_5* pinfo5;

    if (TRUE)
    {
        EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, NULL,
            0, &dwNeeded, &dwReturned);

        pinfo4 = (PRINTER_INFO_4*)malloc(dwNeeded);

        EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, (PBYTE)pinfo4,
            dwNeeded, &dwNeeded, &dwReturned);

        hdc = CreateDC(NULL, pinfo4->pPrinterName, NULL, NULL);

        free(pinfo4);
    }
    return hdc;
}
cell proc_getprinterdc(const cells& c) {
    HDC hdc = GetPrinterDC1();
    cell r(String, para_hdc_str(hdc));
    return r;
}
cell proc_getdevicecaps(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    long arg = atol(c[1].val.c_str());
    int x = GetDeviceCaps(hdc, arg);
    cell r(Number, std::to_string(x));
    return r;
}
cell proc_startdoc(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    static DOCINFO di = { sizeof(DOCINFO), TEXT("Print1: Printing") };
    StartDoc(hdc, &di);
    return true_sym;
}

cell proc_startpage(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    StartPage(hdc);
    return true_sym;
}
cell proc_endpage(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    EndPage(hdc);
    return true_sym;
}
cell proc_enddoc(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    EndDoc(hdc);
    return true_sym;
}
cell proc_deletedc(const cells& c) {
    HDC         hdc = para_str_hdc(c[0].val);
    DeleteDC(hdc);
    return true_sym;
}


//BOOL PrintMyPage(HWND hwnd)
//{
//    static DOCINFO di = { sizeof(DOCINFO), TEXT("Print1: Printing") };
//    BOOL           bSuccess = TRUE;
//    HDC            hdcPrn;
//    int            xPage, yPage;
//
//    if (NULL == (hdcPrn = GetPrinterDC()))
//        return FALSE;
//
//    xPage = GetDeviceCaps(hdcPrn, HORZRES);
//    yPage = GetDeviceCaps(hdcPrn, VERTRES);
//
//    if (StartDoc(hdcPrn, &di) > 0)
//    {
//        //di = { 0 };
//        if (StartPage(hdcPrn) > 0)
//        {
//            PageGDICalls(hdcPrn, xPage, yPage);
//
//            if (EndPage(hdcPrn) > 0)
//                EndDoc(hdcPrn);
//            else
//                bSuccess = FALSE;
//        }
//    }
//    else
//        bSuccess = FALSE;
//
//    DeleteDC(hdcPrn);
//    return bSuccess;
//}
cell proc_RegisterDialogClass(const cells& c) {
    std::string classname = c[0].val;
    std::string dialogproc = c[1].val;
    RegisterDialogClass(0, classname, dialogproc);
    return true_sym;
}

cell proc_DestroyWindow(const cells& c) {
    HWND hwnd = para_str_hwnd(c[0].val);
    DestroyWindow(hwnd);
    return true_sym;
}

cell  proc_MessageBox(const cells& c) {
    checksize(c, 4);
    HWND h = para_str_hwnd(c[0].val);
    std::string body = c[1].val;
    std::string title = c[2].val;
    long a =MessageBox(h,title.c_str(), body.c_str(), atol(c[3].val.c_str()));    
    cell d(Number,std::to_string(a));
    return d;
}
cell  proc_destroymenu(const cells& c) {
    checksize(c, 1);
    HMENU h = para_tohmenu(c[0]);
    BOOL b = DestroyMenu(h);

    return TRUE == b ? true_sym : false_sym;
    //return false_sym;
}
cell proc_DefWindowProc(const cells& c) {
    UINT m = atoi(c[1].val.c_str());;
 
    WPARAM w = para_str_wparam(c[2].val);
    LPARAM l = para_str_lparam(c[3].val);

    HWND hwnd = para_str_hwnd(c[0].val);
    LONG_PTR a= DefWindowProc(hwnd, m, w, l);
    //DefWindowProc(hwnd, 0,0,0);
    
    cell cr(Number, std::to_string(a));
    return cr;
    //return false_sym;
}

cell proc_CreateDialogBox(const cells& c) {
    CreateDialogBox(0, c[0].val, c[1].val);
    return true_sym;
}
void RegisterDialogClass(HWND hwnd, std::string classname, std::string dialogproc) {

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = (WNDPROC)DialogProc;
    wc.hInstance = ghInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszClassName = classname.c_str();
    RegisterClassEx(&wc);
    setdialogproc(classname, dialogproc);

}

void CreateDialogBox(HWND hwnd, std::string classname, std::string title) {
    wstring printerName;
    printerName.assign(title.begin(), title.end());
    CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, classname.c_str(), (LPCSTR)printerName.c_str(),
        WS_VISIBLE | WS_SYSMENU | WS_CAPTION, 100, 100, 200, 150,
        NULL, NULL, ghInstance, NULL);
}


LRESULT CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::string str;
    cell a;
    try {
        char className[MAX_PATH];
        int res = GetClassName(hwnd, className, MAX_PATH);
        std::string winproc;
        if (res > 0) {
            std::string str(&className[0]);
            winproc = getdialogproc(str);
        }
        if (winproc == "")
            winproc = "dialogproc";
        str = "(";
        str += winproc;
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
        if (message == WM_DESTROY) {
            return 0;
        }
    }
    catch (std::string msg) {
        ofstream myFile_Handler;
        myFile_Handler.open("log.txt", std::ios_base::app);
        myFile_Handler << msg << endl;
        myFile_Handler.close();
        exit(2);        
    }
    return (DefWindowProcW(hwnd, message, wParam, lParam));
}

