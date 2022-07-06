(begin(
    (define winproc (lambda (hwnd msg wp lp)
                        (paint1 hwnd msg '123rtya啊或者导致version1.1' 2 )))
    (register (app) "HelloWin1" "winproc")
    (create (app) "HelloWin1")
))