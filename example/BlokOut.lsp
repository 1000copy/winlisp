(begin
    (load '.\lib\constants.lsp')
    (def 
        ptbegin 0 
        ptend 0
        x 0
        y 0
        isblocking #f
        isvalidbox #f
        hdc 0
        ps  0
    )
    (define oncreate (lambda (hwnd )        
        (begin            
            (setwindowtext hwnd 'BlokOut')
            (def rect (list 0 20 300 350))            
            #t
        )
    ))
    (define oncommand(lambda(hwnd msg wp lp)(begin
        (setwindowtext hwnd 'command')
    )))
    (define ondown(lambda(hwnd msg wp lp)(begin
        (set! x (loword lp))
        (set! y (hiword lp))
        (set! ptbegin (list x y))
        (set! ptend (list x y))
        (setwindowtext hwnd (tostring ptbegin))        
        (# mousedown1 hwnd lp)
        (rect_xor hwnd ptbegin ptend)
        (set! isblocking #t)
    )))
    (define onmove(lambda(hwnd msg wp lp)(begin        
        (if isblocking (begin
            (setwindowtext hwnd (tostring ptend)
            (rect_xor hwnd ptbegin ptend)
            (set! x (loword lp))
            (set! y (hiword lp))
            (set! ptend (list x y))
            (rect_xor hwnd ptbegin ptend)
        )))        
        (# mousemove1 hwnd lp)
    )))
    (define onup(lambda(hwnd msg wp lp)(begin        
        (if isblocking (begin
            (setwindowtext hwnd (tostring ptend)
            (rect_xor hwnd ptbegin ptend)
            (set! x (loword lp))
            (set! y (hiword lp))
            (set! ptend (list x y))
            (set! isblocking #f isvalidbox #t)
            (invalidaterect hwnd)
        )))
        
    )))
    (define onpaint(lambda(hwnd msg wp lp)(begin
            (define triple (beginpaint hwnd))
            (set! hdc (nth triple 2))
            (if isvalidbox(begin
                (rect1 hdc ptbegin ptend)
            ))
            (endpaint  triple)        
    )))
    (define onchar(lambda(hwnd msg wp lp)(begin
        (setwindowtext hwnd 'char')
        (if (and isblocking (= wp 27))(begin
            (rect_xor hwnd ptbegin ptend)
            (set! isblocking #f)
        )        
    ))))
    (define winproc (lambda (hwnd msg wp lp)
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
            (if (= WM_LBUTTONDOWN msg)(ondown hwnd msg wp lp) )
            (if (= WM_MOUSEMOVE msg)(onmove hwnd msg wp lp) )
            (if (= WM_LBUTTONUP msg)(onup hwnd msg wp lp) )
            (if (= WM_PAINT msg)(onpaint hwnd msg wp lp) )
            (if (= WM_CHAR msg)(onchar hwnd msg wp lp) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)
