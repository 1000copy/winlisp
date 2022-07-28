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