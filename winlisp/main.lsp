(begin
    (define winproc         (lambda (hwnd msg wp lp)        
        (begin
            (define hdc (beginpaint hwnd))
            (define rect(getclientrect hwnd))
            (drawtext hdc '12345' rect)         
            (endpaint  hdc)
        )
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)