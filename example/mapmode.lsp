(begin
    (load '.\lib\constants.lsp')
    (def dopaint(lambda (hdc)(begin
        (setmapmode hdc MM_ANISOTROPIC)
        (setwindowextent hdc 1 1)
        (setviewextent hdc 100 20)
        (textout hdc  1 1 'helloHI')
        (textout hdc  1 2 'MODE=MM_ANISOTROPIC-hello')
        (setmapmode hdc MM_TEXT)
        (textout hdc  100 60 'MODE=TEXT-helloTEXT')
    )))
    (def onpaint(lambda (hwnd )(begin
            (def triple (beginpaint hwnd ))
            (def hdc (nth triple 2))
            (dopaint hdc)
            (setwindowtext hwnd 'hello')
            (endpaint  triple)
            #t
    )))
    (load '.\lib\entry.lsp')
)

SetWindowExtEx (hdc, 1, 1, NULL) ;
SetViewportExtEx (hdc, cxChar, cyChar, NULL) ;
SetMapMode (hdc, MM_ANISOTROPIC) ;
hdc = (paint_struct hwnd hdc )