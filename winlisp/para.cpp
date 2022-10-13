#include "proc.h"
HMENU para_tohmenu(const cell c) {
    return (HMENU)atoll(c.val.c_str());
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
//太恐怖了，用atoi转换，立刻user32。DefWindowProc报异常，且完全看不懂。
//WPARAM w = atoll(c[2].val.c_str());//unsigned __int64 
//LPARAM l = atoll(c[3].val.c_str());//__int64 //long long  = memory bit 64bit = unsigned __int64= __int64  
WPARAM para_str_wparam(std::string str) {    
    //return atoll(str.c_str());
    return _atoi64(str.c_str());
}

LPARAM para_str_lparam(std::string str) {
    return atoll(str.c_str());

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
    os << "";//"'"is bug
    os << (UINT64)hwnd;
    os << "";//"'" is bug
    return os.str();
    //return std::to_string((UINT64)hwnd);
}
void para_gettriple(const cells& c, int base, HWND& hwnd, HDC& hdc, PAINTSTRUCT& ps) {
    hwnd = para_str_hwnd(c[base].list[0].val);
    hdc = para_str_hdc(c[base].list[2].val);
    para_str_ps_r(c[base].list[1].val, ps);
}