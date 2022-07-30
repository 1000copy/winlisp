(define onpaint(lambda (hwnd )
    (begin
        (define!  texts(
                (--- --- --- )
                ('ab c' abd 3 )
                (1 2 3 )
                (1 2 3 )
            )
            offsets(
                20 100 250
            )
        )
        (define triple (beginpaint hwnd ))
        (define x 0 y 0 offset 0)
        (repeat 4(begin
            (repeat 3 (begin
                (set! offset (nth offsets x))
                (textout triple offset (* y 15) (nth (nth texts y) x))
                (set! x(+ x 1 ))
            ))     
            (set! y(+ y 1 ) x 0)
        ))  
        (endpaint  triple)
        #t
    )
))
