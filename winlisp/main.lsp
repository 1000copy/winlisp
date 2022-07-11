(begin
    (define winproc         (lambda (hwnd msg wp lp)          (paint1 hwnd msg '1234' 2 )                  )    )
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)


