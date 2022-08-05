
#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics [0]))

#include <iostream>
#include <string> 
#include <windows.h>
#include "metric.h"
struct
{
    int     iIndex;
    LPCTSTR szLabel;
    LPCTSTR szDesc;
}
sysmetrics[] =
{
     SM_CXSCREEN,             TEXT("SM_CXSCREEN"),
                              TEXT("Screen width in pixels"),
     SM_CYSCREEN,             TEXT("SM_CYSCREEN"),
                              TEXT("Screen height in pixels"),
     SM_CXVSCROLL,            TEXT("SM_CXVSCROLL"),
                              TEXT("Vertical scroll width"),
     SM_CYHSCROLL,            TEXT("SM_CYHSCROLL"),
                              TEXT("Horizontal scroll height"),
};

void onpaint_metrics(HWND hwnd) {
    static int  cxChar, cxCaps, cyChar;
    HDC         hdc;
    int         i;
    PAINTSTRUCT ps;
    TCHAR       szBuffer[10];
    TEXTMETRIC  tm;
    hdc = GetDC(hwnd);

    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
    cyChar = tm.tmHeight + tm.tmExternalLeading;

    ReleaseDC(hwnd, hdc);
    hdc = BeginPaint(hwnd, &ps);

    for (i = 0; i < NUMLINES; i++)
    {
        TextOut(hdc, 0, cyChar * i,
            sysmetrics[i].szLabel,
            lstrlen(sysmetrics[i].szLabel));

        TextOut(hdc, 22 * cxCaps, cyChar * i,
            sysmetrics[i].szDesc,
            lstrlen(sysmetrics[i].szDesc));

        SetTextAlign(hdc, TA_RIGHT | TA_TOP);
        std::string b = "     ";
        b += std::to_string(GetSystemMetrics(sysmetrics[i].iIndex));
        b = b.substr(b.size() - 5, 5);
        int a = wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].iIndex));
        TextOut(hdc, 22 * cxCaps + 40 * cxChar, cyChar * i, szBuffer, a);
        SetTextAlign(hdc, TA_LEFT | TA_TOP);
    }
    EndPaint(hwnd, &ps);
}
void onpaint1(HWND hwnd) {
    static int  cxChar, cxCaps, cyChar;
    HDC         hdc;
    int         i;
    PAINTSTRUCT ps;
    //TCHAR       szBuffer[10];
    TEXTMETRIC  tm; 
    hdc = GetDC(hwnd);

    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
    cyChar = tm.tmHeight + tm.tmExternalLeading;

    ReleaseDC(hwnd, hdc);
    hdc = BeginPaint(hwnd, &ps);

    for (i = 0; i < NUMLINES; i++)
    {
        TextOut(hdc, 0, cyChar * i,
            sysmetrics[i].szLabel,
            lstrlen(sysmetrics[i].szLabel));

        TextOut(hdc, 22 * cxCaps, cyChar * i,
            sysmetrics[i].szDesc,
            lstrlen(sysmetrics[i].szDesc));

        SetTextAlign(hdc, TA_RIGHT | TA_TOP);
        std::wstring b = L"     ";
        b += std::to_wstring(GetSystemMetrics(sysmetrics[i].iIndex));
        b = b.substr(b.size() - 5, 5);
        LPCWSTR e = b.c_str();
        TextOut(hdc, 22 * cxCaps + 40 * cxChar, cyChar * i,(LPCSTR)e, 5);
        SetTextAlign(hdc, TA_LEFT | TA_TOP);
    }
    EndPaint(hwnd, &ps);
}