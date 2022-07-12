(begin
    (define winproc         (lambda (hwnd msg wp lp)        
        (begin
            (define hdc (beginpaint hwnd))
            (drawtext hdc '1234' 10 10 200 20)
            (line hdc  10 10 200 20)
            (endpaint  hdc)
        )
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)


