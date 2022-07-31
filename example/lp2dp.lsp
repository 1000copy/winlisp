(begin
    (load '.\lib\constants.lsp')
    (def dopaint(lambda (hdc rect)(begin
        (lr2dr hdc MM_LOMETRIC rect)
    )))
    (def onpaint(lambda (hwnd )(begin
            (def triple (beginpaint hwnd ))
            (def hdc (nth triple 2))
            (define rect(getclientrect hwnd))
            (def abc(dopaint hdc rect))
            (setwindowtext hwnd abc)
            (endpaint  triple)
            #t
    )))
    (load '.\lib\entry.lsp')
)
-----------END OF CODE
(def rect(lr2dr hdc mapmode rect))
GetClientRect (hwnd, &rect) ;

SaveDC (hdc) ;
SetMapMode (hdc, iMapMode) ;
DPtoLP (hdc, (PPOINT) &rect, 2) ;
RestoreDC (hdc, -1) ;