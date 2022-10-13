(begin
    (load '.\lib\constants.lsp')
    (def!  texts(
            (SM_CXSCREEN 'SM_CXSCREEN' 'Screen width in pixels')
            (SM_CYSCREEN 'SM_CYSCREEN' 'Screen height in pixels')   
    ))
    (define hlistview 0)
    (define oncreate (lambda (hwnd )        
        (begin
            (def rect(getclientrect hwnd))
            (set! hlistview(lv_create hwnd rect))
            (lv_setcolumns hlistview (list 'id' 'name' 'comment') (list 200 150 250))
            (def i 0 id 0 c1 0 c2 0)
            (repeat (length texts)(begin
                (set! id (getsystemmetrics (nth (nth texts i)0)))
                (set! c1 (nth (nth texts i)1))
                (set! c2 (nth (nth texts i)2))
                (lv_appenditem hlistview (+ i 1)(list  c1 id c2))
                (set! i(+ i 1))
            ))
            #t
        )
    ))
    (define keyview (lambda (hwnd msg wp lp)
        (begin
            (def keyname (GetKeyNameText lp))
            (setwindowtext hwnd keyname)
            (lv_appenditem hlistview 0 (list  keyname keyname keyname))
            #t
        )
    ))
    (define winproc (lambda (hwnd msg wp lp)
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
            (if (= WM_CHAR msg)(keyview hwnd msg wp lp)) 
            (DefWindowProc hwnd msg wp lp )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)

GetKeyNameText (pmsg[i].lParam, szKeyName, 
                               sizeof (szKeyName) / sizeof (TCHAR)) ;
TextOut (hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer,
        wsprintf (szBuffer, szFormat [iType],
                szMessage [pmsg[i].message - WM_KEYFIRST],                   
                pmsg[i].wParam,
                (PTSTR) (iType ? TEXT (" ") : szKeyName),
                (TCHAR) (iType ? pmsg[i].wParam : ' '),
                LOWORD (pmsg[i].lParam),
                HIWORD (pmsg[i].lParam) & 0xFF,
                0x01000000 & pmsg[i].lParam ? szYes  : szNo,
                0x20000000 & pmsg[i].lParam ? szYes  : szNo,
                0x40000000 & pmsg[i].lParam ? szDown : szUp,
                0x80000000 & pmsg[i].lParam ? szUp   : szDown)) ;