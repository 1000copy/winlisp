(begin
    (load '.\lib\constants.lsp')
    (def! texts (
        (MM_TEXT 'MM_TEXT')
        (MM_LOMETRIC 'MM_LOMETRIC')
        (MM_HIMETRIC 'MM_HIMETRIC')
        (MM_LOENGLISH 'MM_LOENGLISH')
        (MM_HIENGLISH 'MM_HIENGLISH')
        (MM_TWIPS 'MM_TWIPS')
    ))
    (def! offsets(
            20 100 250 300
    ))
    (def! titles(
            mode text right bottom
    ))
    (def onpaint(lambda (hwnd )(begin
            (def value 0 rect 0)
            (def triple (beginpaint hwnd ))
            (def hdc (nth triple 2))
            (def x 0 y 0 offset 0 mapmode 0 bottom 0 right 0 yoffset 0 index 0)    
            (repeat 4 (begin
                (textout hdc (nth offsets index) 0 (nth titles index))
                (textout hdc (nth offsets index) 25 '--------')
                (set! index(+ index 1))
            )) 
            (def rect (getclientrect hwnd)) 
            (repeat 6(begin
                (set! yoffset (+ (* y 25) 50))
                (set! offset (nth offsets 0))
                (set! value (nth(nth texts y)0))
                (set! mapmode (eval value))
                (textout hdc offset yoffset  mapmode)               

                (set! offset (nth offsets 1))
                (set! value (nth(nth texts y)0))
                (textout hdc offset yoffset  value)   
                
                (set! right (nth (lr2dr hdc mapmode rect) 2) )
                (set! offset (nth offsets 2))
                (textout hdc offset yoffset right)

                (set! bottom (nth (lr2dr hdc mapmode rect) 3) )
                (set! offset (nth offsets 3))
                (textout hdc offset yoffset bottom)
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

(set! value (eval (nth (nth texts y) x)))
(set! rect(lr2dr hdc value (getclientrect hwnd)))
(setwindowtext hwnd (eval(nth (nth texts 0) 0)))