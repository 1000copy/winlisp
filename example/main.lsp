  (begin
    (load '.\lib\constants.lsp')
    (def onpaint(lambda (hwnd )
        (begin
            (def triple (beginpaint hwnd ))
            (def rect(getclientrect hwnd ))
            (def hdc (nth triple 2))
            (drawtext hdc 'hello,world!' rect)         
            (endpaint  triple)
            #t
        )
    ))
    (define handled (lambda (msg)(or (= WM_PAINT msg) (= WM_DESTROY msg))))
    (define winproc         (lambda (hwnd msg wp lp )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd ))
            (if (= WM_DESTROY msg)(quit) )
            (if (not (handled msg)) (DefWindowProc hwnd msg wp lp ) 0)
        )                
    ))
    (register (app) 'HelloWin' )
    (create (app) 'HelloWin')
  )