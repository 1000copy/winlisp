#include "listview.h"
#include <tchar.h>
#include "lchar.h"
//depreciated
void InsertColumn(HWND hList) {
    LVCOLUMN  LvCol;
    memset(&LvCol, 0, sizeof(LvCol));
    LvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    LvCol.cx = 100;
    LvCol.pszText = (__STR)_T("Item");
    SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol);
    LvCol.cx = 200;
    LvCol.pszText = (__STR)_T("Sub Item111");
    SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol);
    LvCol.cx = 300;
    LvCol.pszText = (__STR)_T("Sub Item2");
    SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol);
}
//depreciated
void AppendItem(HWND hList) {
    LVITEM LvItem;
    TCHAR buffer[256];
    //LVCOLUMN  LvCol;
    memset(&LvItem, 0, sizeof(LvItem)); // Zero struct's Members
        //  Setting properties Of members:
    for (int j = 1; j <= 11; j++) // Add SubItems in a loop
    {
        wsprintf(buffer, (__CSTR)_T("%3d"), j);
        LvItem.mask = LVIF_TEXT;   // Text Style
        LvItem.cchTextMax = 256; // Max size of test
        LvItem.iItem = 0;          // choose item  
        LvItem.iSubItem = 0;       // Put in first coluom
        LvItem.pszText = buffer;

        SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&LvItem); // Send info to the Listview

        for (int i = 1; i <= 2; i++) // Add SubItems in a loop
        {
            LvItem.iSubItem = i;            
            wsprintf(buffer, (__CSTR)_T("SubItem %d"), i);
            LvItem.pszText = buffer;
            SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&LvItem); // Enter text to SubItems
        }
    }
}
HWND CreateListView(HWND hwndParent, HMENU ID, RECT rcClient)
{
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);


    // Create the list-view window in report view with label editing enabled.    
    HWND hWndListView = CreateWindow(WC_LISTVIEW, //ERROR red line under create window
        (__STR)_T("yach"),
        //WS_CHILD | LVS_REPORT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT,
        WS_CHILD | LVS_REPORT | LVS_EX_GRIDLINES ,
        rcClient.left, rcClient.top,
        rcClient.right, rcClient.bottom,
        hwndParent,
        (HMENU)ID, //ERROR IDM CODE SAMPLES undefined
        GetModuleHandle(nullptr), //ERROR
        NULL);
    ShowWindow(hWndListView, 1);
    return (hWndListView);
}