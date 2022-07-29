(define onpaint(lambda (hwnd )
    (begin
        (define hdc (beginpaint hwnd ))
        (define rect(getclientrect hwnd ))
        (drawtext hdc 'hello,world!' rect)         
        (line hdc 10 10 100 200)
        (endpaint  hdc)
        #t
    )
))