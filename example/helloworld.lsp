(begin
    (load '.\lib\constants.lsp')
    (def onpaint(lambda (hwnd )
        (begin
            (def triple (beginpaint hwnd ))
            (def rect(getclientrect hwnd ))
            (def hdc (nth triple 2))
            (drawtext hdc 'hello,world!' rect)         
            (line hdc 10 10 100 200)
            (endpaint  triple)
            #t
        )
    ))
    (load '.\lib\entry.lsp')
)