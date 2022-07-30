(begin
    (load '.\lib\constants.lsp')
    (define onpaint         (lambda (hwnd )        
        (begin
            (define hdc (beginpaint hwnd))
            (define rect(getclientrect hwnd))
            (drawtext hdc '1234' 10 10 200 20)
            (drawtext hdc '1234' (nth rect 0) (nth rect 1) (nth rect 2) (nth rect 3) )
            (drawtext hdc '1234' rect)
            (line hdc  10 10 200 20)
            (endpaint  hdc)
            #t
        )
    ))
    (define winproc         (lambda (hwnd msg )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd))
            (if (= WM_DESTROY msg)(quit) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)


