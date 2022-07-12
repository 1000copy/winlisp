(begin
    (define winproc         (lambda (hwnd msg wp lp)        
        (begin
            (define hdc (beginpaint hwnd))
            (define rect(getclientrect hwnd))
            (p rect)
            (drawtext hdc '1234' 10 10 200 20)
            (drawtext hdc '1234' (nth rect 0) (nth rect 1) (nth rect 2) (nth rect 3) )
            (drawtext hdc '1234' rect)
            (line hdc  10 10 200 20)
            (endpaint  hdc)
        )
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)


