(begin
    (load '.\lib\constants.lsp')
    (def onpaint(lambda (hwnd )
        (begin
            (def triple (beginpaint hwnd ))
            (def rect(getclientrect hwnd ))
            (def hdc (nth triple 2))
            (drawtext hdc 'hello,named winproc!' rect)            
            (endpaint  triple)
            #t
        )
    ))
    (define winproc1(lambda (hwnd msg wp lp )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd ))
            (if (= WM_DESTROY msg)(quit) )
        )                
    ))
    (register (app) 'HelloWin1' 'winproc1')
    (create (app) 'HelloWin1')
)