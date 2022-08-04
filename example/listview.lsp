(begin
    (load '.\lib\constants.lsp')
    (def!  texts(
            (SM_CXSCREEN,"SM_CXSCREEN","Screen width in pixels")
            (SM_CYSCREEN,"SM_CYSCREEN","Screen height in pixels")
        )
        offsets(
            20 100 250
        )
    )
    (define oncreate (lambda (hwnd )        
        (begin
            (def rect(getclientrect hwnd))
            (def hlistview(lv_create hwnd rect))
            (lv_setcolumns hlistview (list 'id' 'name' 'comment'))
            (lv_appenditem hlistview (list 'id1' 'name1' 'comment1'))
            (lv_appenditem hlistview (list 'id2' 'name1' 'comment1'))
            #t
        )
    ))
    (define winproc         (lambda (hwnd msg )
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)


