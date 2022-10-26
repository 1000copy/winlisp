#pragma once
#include <windows.h>
#include <commctrl.h>
#pragma comment(lib,"Comctl32.lib")
HWND CreateListView(HWND, HMENU, RECT);
void InsertColumn(HWND hList);
void AppendItem(HWND hList);
/*
GetClientRect(hwnd, &rcClient);
        hList = CreateListView(hwnd, IDM_CODE_SAMPLES,rcClient);
        InsertColumn(hList);
        AppendItem(hList);        
        */