(begin
    (load '.\lib\constants.lsp')
    (define MM_ANISOTROPIC 8)
    (define onpaint(lambda (hwnd )
        (begin
            (define triple (beginpaint hwnd ))
            (define hdc (nth triple 2))
            (setmapmode hdc MM_ANISOTROPIC)
            (setwindowextent hdc 1 1)
            (setviewextent hdc 100 20)
            (textout hdc  1 1 'hello')
            (textout hdc  1 2 'hello')
            (setwindowtext hwnd 'hello')
            (endpaint  triple)
            #t
        )
    ))
    (load '.\lib\entry.lsp')
)

SetWindowExtEx (hdc, 1, 1, NULL) ;
SetViewportExtEx (hdc, cxChar, cyChar, NULL) ;
SetMapMode (hdc, MM_ANISOTROPIC) ;
hdc = (paint_struct hwnd hdc )