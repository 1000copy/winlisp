  (begin
    (define winproc         (lambda (hwnd msg )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd ))
            (if (= WM_DESTROY msg)(quit) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
  )