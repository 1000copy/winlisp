(begin
    (load '.\lib\constants.lsp')
    (def 
        ptbegin 0 
        ptend 0
        isblocking 0
        isvalidbox 0
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
        (setwindowtext hwnd 'd')
        (mousedown1 hwnd lp)
    )))
    (define onmove(lambda(hwnd msg wp lp)(begin
        (setwindowtext hwnd 'm')
        (mousemove1 hwnd lp)
    )))
    (define onup(lambda(hwnd msg wp lp)(begin
        (setwindowtext hwnd 'u')
        (mouseup1 hwnd lp)
    )))
    (define onpaint(lambda(hwnd msg wp lp)(begin
            (define triple (beginpaint hwnd))
            (def hdc (nth triple 2))
            (paint1 hdc)    
            (endpaint  triple)        
    )))
    (define onchar(lambda(hwnd msg wp lp)(begin
        (setwindowtext hwnd 'char')
        (char1 hwnd wp)
    )))
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
