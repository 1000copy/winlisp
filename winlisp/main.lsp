(begin
    (define WM_PAINT 15)
    (define WM_DESTROY 2)
    (define onpaint(lambda (hwnd)
        (begin
            (define hdc (beginpaint hwnd))
            (define rect(getclientrect hwnd))
            (drawtext hdc '12345' rect)         
            (endpaint  hdc)
            #t
        )
    ))
    (define winproc         (lambda (hwnd msg wp )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd))
            (if (= WM_DESTROY msg)(quit) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)