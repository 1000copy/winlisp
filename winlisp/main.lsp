(begin(
    (define winproc         (lambda (hwnd msg wp lp)          (paint1 hwnd msg '123' 2 )                  )    )
    (register (app) 'HelloWin1' 'winproc')
    (create (app) 'HelloWin1')
))
