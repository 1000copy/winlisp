(begin
    (load '.\lib\constants.lsp')
    (def bottom 0 i 0)
    (def onpaint(lambda (hwnd )
        (begin
            (def triple (beginpaint hwnd ))
            (def hdc (nth triple 2))
            (def rect (getclientrect hwnd))
            (def tr(gettextmetrics hwnd))
            (drawtext hdc (cat (car tr) '-' (nth tr 1) '-' (nth tr 2)) rect)    
            (set! bottom (nth rect 3))
            (textout hdc 100 100 (/ bottom (nth tr 1)))     
            (repeat 21 (begin
                (textout hdc 10 (* (nth tr 1) i) (cat 'placeholder' i))
                (set! i(+ i 1))
            ))
            (endpaint  triple)            
            #t
        )
    ))
    (load '.\lib\entry.lsp')
)