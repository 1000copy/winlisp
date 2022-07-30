(begin
    (load '.\lib\constants.lsp')    
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
                    (define hdc (nth triple 2))
                    (textout hdc offset (* y 15) (nth (nth texts y) x))
                    (set! x(+ x 1 ))
                ))     
                (set! y(+ y 1 ) x 0)
            ))  
            (endpaint  triple)
            #t
        )
    ))
    (load '.\lib\entry.lsp')
)
0x0000001c7fb03480
0x0000001c7fb03480
any text or comment
hdc = (paint_struct hwnd hdc )
append error to log file(notdefinedfunctionerror)
ref. WhatSize.c - 
implement SetMapMode,SetWindowOrg,SetViewOrg,SetWindowExtent,SetViewExtent