(begin
    (load '.\lib\constants.lsp')
    (def style 0 idList 1 idStatic 2 hwnd_list 0 hwnd_static 0 title '')
    (define oncreate (lambda (hwnd )        
        (begin            
            (setwindowtext hwnd 'environ')
            (def rect (list 0 20 300 350))
            (set! hwnd_list(createlistbox hwnd style idList title rect))
            (def rect (list 0 0 300 20))
            (set! hwnd_static(createstatic hwnd style idStatic title rect))
            (def texts(GetEnvironmentStrings))            
            (repeat (length texts)(begin
                (ls_add hwnd_list(car texts))
                (set! texts (cdr texts))
            ))            
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
            (def a (ls_getsel hwnd_list))
            (setwindowtext hwnd_static a)
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