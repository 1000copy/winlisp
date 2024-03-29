(begin
    (load '.\lib\constants.lsp')
    (def!  texts (
                (BS_PUSHBUTTON      1 'PUSHBUTTON')
                (BS_DEFPUSHBUTTON   2   'DEFPUSHBUTTON')
                (BS_CHECKBOX        3   'CHECKBOX') 
                (BS_AUTOCHECKBOX    4 'AUTOCHECKBOX')
                (BS_RADIOBUTTON     5 'RADIOBUTTON')
                (BS_3STATE          6 '3STATE')
                (BS_AUTO3STATE      7 'AUTO3STATE')
                (BS_GROUPBOX        8 'GROUPBOX')
                (BS_AUTORADIOBUTTON   9  'AUTORADIO')
                (BS_OWNERDRAW          10 'OWNERDRAW')
    ))
    (define oncreate (lambda (hwnd )        
        (begin
            (def i 0 style 0 id 0 title 0)
            (setwindowtext hwnd 'btnlook')
            (def rect 0)
            (repeat (length texts) (begin 
                (set! style (eval (nth (nth texts i) 0)))
                (set! id (eval (nth (nth texts i) 1)))
                (set! title (eval (nth (nth texts i) 2)))
                (set! rect(list 0 (* 35 i) 150 30))
                (createbutton hwnd style id title rect)
                (set! i(+ i 1))
            ))
            #t
        )
    ))
    (define oncommand(lambda(hwnd msg wp lp)(begin
        (if (= (hiword wp) BN_CLICKED)(begin
            (#      here's comment
                    button id [loword wp]
                    button hwnd [HWND]lParam
                    HIWORD[wParam] == BN_CLICKED
            )
            (setwindowtext lp (loword wp))
            (setwindowtext hwnd (loword wp))
    )))))
    (define winproc (lambda (hwnd msg wp lp)
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
            (if (= WM_COMMAND msg)(oncommand hwnd msg wp lp) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)