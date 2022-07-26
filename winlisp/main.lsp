(begin
    (define WM_PAINT 15)
    (define WM_DESTROY 2)
    (define onpaint(lambda (hwnd )
        (begin
            (define hdc (beginpaint hwnd ))
            (define rect(getclientrect hwnd ))
            (drawtext hdc '0099' rect)         
            (line hdc 10 10 100 200)
            (endpaint  hdc)
            #t
        )
    ))
    (define winproc         (lambda (hwnd msg )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd ))
            (if (= WM_DESTROY msg)(quit) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)
0x0000001c7fb03480
0x0000001c7fb03480
any text or comment