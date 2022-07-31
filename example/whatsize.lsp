(begin
    (load '.\lib\constants.lsp')
    (def! texts (
        (MM_TEXT "MM_TEXT")
        (MM_LOMETRIC "MM_LOMETRIC")
        (MM_HIMETRIC "MM_HIMETRIC")
        (MM_LOENGLISH "MM_LOENGLISH")
        (MM_HIENGLISH "MM_HIENGLISH")
        (MM_TWIPS "MM_TWIPS")
    ))
    (def! offsets(
            20 200 
        )
    )
    (def dopaint(lambda (hdc rect)(begin
        (lr2dr hdc MM_LOMETRIC rect)
    )))
    (def onpaint(lambda (hwnd )(begin
            (def triple (beginpaint hwnd ))
            (def hdc (nth triple 2))
                        (def x 0 y 0 offset 0)
            (repeat 6(begin
                (repeat 2 (begin
                    (set! offset (nth offsets x))
                    (def hdc (nth triple 2))
                    (textout hdc offset (* y 25) (nth (nth texts y) x))
                    (set! x(+ x 1 ))
                ))     
                (set! y(+ y 1 ) x 0)
            ))  
            (endpaint  triple)
            #t
    )))
    (load '.\lib\entry.lsp')
)

Show (hwnd, hdc, 1, 3, MM_TEXT,      TEXT ("TEXT (pixels)")) ;
Show (hwnd, hdc, 1, 4, MM_LOMETRIC,  TEXT ("LOMETRIC (.1 mm)")) ;
Show (hwnd, hdc, 1, 5, MM_HIMETRIC,  TEXT ("HIMETRIC (.01 mm)")) ;
Show (hwnd, hdc, 1, 6, MM_LOENGLISH, TEXT ("LOENGLISH (.01 in)")) ;
Show (hwnd, hdc, 1, 7, MM_HIENGLISH, TEXT ("HIENGLISH (.001 in)")) ;
Show (hwnd, hdc, 1, 8, MM_TWIPS,     TEXT ("TWIPS (1/1440 in)")) ;