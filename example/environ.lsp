(begin
    (load '.\lib\constants.lsp')
    (def style 0 idList 1 idStatic 2 hwnd1 0 hwnd2 0 title '')
    (define oncreate (lambda (hwnd )        
        (begin            
            (setwindowtext hwnd 'environ')
            (def rect (list 0 20 300 350))
            (set! hwnd1(createlistbox hwnd style idList title rect))
            (def rect (list 0 0 300 20))
            (set! hwnd2(createstatic hwnd style idStatic title rect))
            (setwindowtext hwnd2 'undefined')
            #t
        )
    ))
    (define oncommand(lambda(hwnd msg wp lp)(begin
        (if (= (hiword wp) LBN_SELCHANGE)(begin
            (#      here's comment
                    button id [loword wp]
                    button hwnd [HWND]lParam
                    HIWORD[wParam] == BN_CLICKED
                    (setwindowtext lp (loword wp))
                    (setwindowtext hwnd (loword wp))
            )            
            (def a (ls_getsel hwnd1))
            (setwindowtext hwnd2 a)
    )))))
    (define winproc (lambda (hwnd msg wp lp)
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
            (#
                (if (= WM_COMMAND msg)(oncommand hwnd msg wp lp) )
            )
            (if (= WM_COMMAND msg)(oncommand hwnd msg wp lp) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)

void FillListBox (HWND hwndList) 
{
     int     iLength ;
     TCHAR * pVarBlock, * pVarBeg, * pVarEnd, * pVarName, * pVarBlockHead ;

     pVarBlockHead = pVarBlock = GetEnvironmentStrings () ;  // Get pointer to environment block

     while (*pVarBlock)
     {
          if (*pVarBlock != '=')   // Skip variable names beginning with '='
          {
               pVarBeg = pVarBlock ;              // Beginning of variable name
               while (*pVarBlock++ != '=') ;      // Scan until '='
               pVarEnd = pVarBlock - 1 ;          // Points to '=' sign
               iLength = pVarEnd - pVarBeg ;      // Length of variable name

                    // Allocate memory for the variable name and terminating
                    // zero. Copy the variable name and append a zero.

               pVarName = calloc (iLength + 1, sizeof (TCHAR)) ;
               CopyMemory (pVarName, pVarBeg, iLength * sizeof (TCHAR)) ;
               pVarName[iLength] = '\0' ;

                    // Put the variable name in the list box and free memory.

               SendMessage (hwndList, LB_ADDSTRING, 0, (LPARAM) pVarName) ;
               free (pVarName) ;
          }
          while (*pVarBlock++ != '\0') ;     // Scan until terminating zero
     }
     FreeEnvironmentStrings (pVarBlockHead) ;
}

     case WM_COMMAND :
          if (LOWORD (wParam) == ID_LIST && HIWORD (wParam) == LBN_SELCHANGE)
          {
                    // Get current selection.

               iIndex  = SendMessage (hwndList, LB_GETCURSEL, 0, 0) ;
               iLength = SendMessage (hwndList, LB_GETTEXTLEN, iIndex, 0) + 1 ;
               pVarName = calloc (iLength, sizeof (TCHAR)) ;
               SendMessage (hwndList, LB_GETTEXT, iIndex, (LPARAM) pVarName) ;

                    // Get environment string.

               iLength = GetEnvironmentVariable (pVarName, NULL, 0) ;
               pVarValue = calloc (iLength, sizeof (TCHAR)) ;
               GetEnvironmentVariable (pVarName, pVarValue, iLength) ;

                    // Show it in window.
               
               SetWindowText (hwndText, pVarValue) ;
               free (pVarName) ;
               free (pVarValue) ;
          }
          return 0 ;