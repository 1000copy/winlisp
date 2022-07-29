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
        (repeat 3(begin
            (repeat 3 (begin
                (set! offset (nth offsets x))
                (textout triple offset (* y 15) (nth (nth texts y) x))
                (set! x(+ x 1 ))
            ))     
            (set! y(+ y 1 ))
            (set! x 0)
        ))  
        (endpaint  triple)
        #t
    )
))
there comment go
triple == hwnd hdc paintstructure
repeat x action
repeat y action
TODO:
    textout 只要指定x,y，不需要指定rect，和drawtext相比，要省事一点。
    (++ x )  = (set! x(+ x 1 ))
    (define! offsets (0 100 100))  ====
        (define offsets(quote(
           0 100 100
        )))
