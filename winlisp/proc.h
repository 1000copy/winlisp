#pragma once
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <streambuf>
#include "..\lisp\lisp.h"
#include "metric.h"
#include "listview.h"
void add_winglobals(environment& global_env);
typedef struct tagtriple {
    int  cxChar, cyChar, cxCaps;
} triple;

cell proc_beginpaint(const cells& c);
cell proc_endpaint(const cells& c);
HMENU para_tohmenu(const cell c);
POINT para_getpoint(const cell& c);
void para_getrect(const cells& c, int base, RECT& rect);
cell proc_tostring(const cells& c);
PAINTSTRUCT* para_str_ps(std::string str);
void para_str_ps_r(std::string str, PAINTSTRUCT& ps);
std::string para_ps_str(PAINTSTRUCT* p);

HWND para_str_hwnd(std::string str);
std::string para_hwnd_str(HWND  hwnd);

HDC para_str_hdc(std::string str);
std::string para_hdc_str(HDC  hwnd);
void para_gettriple(const cells& c, int base, HWND& hwnd, HDC& hdc, PAINTSTRUCT& ps);
cell proc_load(const cells& c);
cell proc_drawtext(const cells& c);
cell proc_app(const cells& c);
cell proc_register(const cells& c);
cell proc_create1(const cells& c);
void Rectangle1(HDC hdc, int l, int t, int r, int b);
void rect_xor(HWND hwnd, POINT ptBeg, POINT ptEnd);
cell proc_invalidaterect(const cells& c);
cell proc_rect_xor(const cells& c);

cell proc_rect1(const cells& c);
ATOM registerclass(HINSTANCE hInstance, std::string app);
HWND createwindow(HINSTANCE hInstance, std::string app);
triple gettextmetrics(HWND hwnd);
cell proc_GetKeyNameText(const cells& c);
cell proc_gettextmetrics(const cells& c);
cell proc_getsystemmetrics(const cells& c);
cell proc_app(const cells& c);
cell proc_quit(const cells& c);
cell proc_register(const cells& c);
cell proc_create1(const cells& c);

cell proc_drawtext(const cells& c);
cell proc_textout(const cells& c);
cell proc_lv_create(const cells& c);
cell proc_lv_setcolumns(const cells& c);

cell proc_lv_appenditem(const cells& c);
cell proc_loword(const cells& c);
cell proc_hiword(const cells& c);

cell proc_createbutton(const cells& c);
cell proc_ls_getsel(const cells& c);
cell proc_ls_add(const cells& c);
cell proc_GetEnvironmentStrings(const cells& c);
cell proc_createlistbox(const cells& c);
cell proc_createstatic(const cells& c);
cell proc_setwindowtext(const cells& c);


cell proc_trap(const cells& c);
cell proc_eval(const cells& c);
cell proc_setmapmode(const cells& c);
cell proc_setwindowextent(const cells& c);
cell proc_setviewextent(const cells& c);
cell proc_line(const cells& c);
void onpaint(HWND hwnd);

cell proc_getclientrect(const cells& c);
//(def rect(lr2dr hdc mapmode rect))
cell proc_lr2dr(const cells& c);
cell proc_appendmenu(const cells& c);
cell proc_getsystemmenu(const cells& c);
cell proc_createmenu(const cells& c);
cell proc_setmenu(const cells& c);
cell proc_moveto(const cells& c);
cell proc_lineto(const cells& c);
cell proc_savedc(const cells& c);
cell proc_restoredc(const cells& c);
cell proc_setlogicalextent(const cells& c);
cell proc_setdeviceextent(const cells& c);
cell proc_setdeviceorigin(const cells& c);
cell proc_ellipse(const cells& c);

cell proc_getprinterdc(const cells& c);
cell proc_getdevicecaps(const cells& c);
cell proc_startdoc(const cells& c);
cell proc_startpage(const cells& c);
cell proc_endpage(const cells& c);
cell proc_enddoc(const cells& c);
cell proc_deletedc(const cells& c);
std::string getwinproc(std::string classname);
std::string getdialogproc(std::string classname);
void setdialogproc(std::string, std::string);
cell proc_RegisterDialogClass(const cells& c);
cell proc_CreateDialogBox(const cells& c);
cell proc_DestroyWindow(const cells& c);