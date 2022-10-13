  (begin
    (define handled (lambda (msg)(or 
                    (= WM_PAINT msg)
                    (= WM_DESTROY msg)                    
                )))
    (define winproc         (lambda (hwnd msg wp lp )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd ))
            (if (= WM_DESTROY msg)(quit) )
            (# if (not (handled msg)) (DefWindowProc hwnd msg wp lp ))
            (DefWindowProc hwnd msg wp lp )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
  )