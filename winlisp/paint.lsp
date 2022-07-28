(define onpaint(lambda (hwnd )
    (begin
        (define texts(quote(
            ('ab c' abd 3 )
            (1 2 3 )
            (1 2 3 )
        )))
        (define offsets(quote(
           0 100 100
        )))
        (define hdc (beginpaint hwnd ))
        (define x 0)
        (define xx 0)
        (repeat 3 (begin
          (set! xx (* 100 x))
          (quote(drawtext hdc (nth (nth texts 0) x) xx 0 (+ xx 100) 100))
          (textout hdc xx 0 (nth (nth texts 0) x))
          (set! x(+ x 1 ))
        ))       
        (endpaint  hdc)
        #t
    )
))
repeat x action
repeat y action
TODO:
    textout 只要指定x,y，不需要指定rect，和drawtext相比，要省事一点。
    (++ x )  = (set! x(+ x 1 ))
    (define! offsets (0 100 100))  ====
        (define offsets(quote(
           0 100 100
        )))