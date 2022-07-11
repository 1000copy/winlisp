(begin
    (define winproc 0 )
    (set! winproc         (lambda (hwnd msg wp lp)          (paint1 hwnd msg '123' 2 )                  )    )
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)


