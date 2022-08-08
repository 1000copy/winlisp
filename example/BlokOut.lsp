(begin
    (load '.\lib\constants.lsp')
    (def style 0 id_list 1 id_static 2 hwnd_list 0 hwnd_static 0 title '')
    (define oncreate (lambda (hwnd )        
        (begin            
            (setwindowtext hwnd 'BlokOut')
            (def rect (list 0 20 300 350))            
            #t
        )
    ))
    (define oncommand(lambda(hwnd msg wp lp)(begin

    )))
    (define winproc (lambda (hwnd msg wp lp)
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
            (if (= WM_COMMAND msg)(oncommand hwnd msg wp lp) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)
