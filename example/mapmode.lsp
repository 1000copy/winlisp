(begin
    (load '.\lib\constants.lsp')
    (define MM_ANISOTROPIC 8)
    (define onpaint(lambda (hwnd )
        (begin
            (define triple (beginpaint hwnd ))
            (setmapmode triple MM_ANISOTROPIC)
            (setwindowextent triple 1 1)
            (setviewextent triple 100 20)
            (textout triple  1 1 'hello')
            (textout triple  1 2 'hello')
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
