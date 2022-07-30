(begin
    (load '.\lib\constants.lsp')
    (define onpaint(lambda (hwnd )
        (begin
            (define triple (beginpaint hwnd ))
            (define rect(getclientrect hwnd ))
            (define hdc (nth triple 2))
            (drawtext hdc 'hello,world!' rect)         
            (line hdc 10 10 100 200)
            (endpaint  triple)
            #t
        )
    ))
    (load '.\lib\entry.lsp')
)