(begin
    (load '.\lib\constants.lsp')
    (def cx 0 cy 0 hdc 0)    
    (def pageprint(lambda (hdc cx cy )(begin        
            (moveto hdc 0 0)
            (lineto hdc cx cy)
            (moveto hdc cx 0)
            (lineto hdc 0 cy)
            (setmapmode hdc MM_ISOTROPIC )
            (setlogicalextent hdc 1000 1000)
            (setdeviceextent hdc (/ cx 2 ) (* -1(/ cy 2)))
            (setdeviceorigin hdc (/ cx 2 ) (* 1(/ cy 2)))
            (ellipse hdc -500 500 500 -500)
            (restoredc hdc)
    
    )))
    (def onpaint(lambda (hwnd )
        (begin
            (def triple (beginpaint hwnd ))
            (def hdc (nth triple 2))
            (# draw X diagram)
            (pageprint hdc cx cy)
            (endpaint  triple)
            #t
        )
    ))
    (def hmenu 0 hmenubar 0)
    (def oncreate(lambda (hwnd msg wp lp)
        (begin
            (set! hmenu (getsystemmenu hwnd ))
            (appendmenu hmenu MF_SEPARATOR 0 '')
            (appendmenu hmenu MF_STRING 1 'print')
            #t
        )
    ))
    (def onsize(lambda (hwnd msg wp lp)
        (begin
            (set! cx (loword lp) cy(hiword lp))
            (setwindowtext hwnd (tostring(list cx cy)))
            #t
        )
    ))    
    (def onprint(lambda (hwnd msg wp lp)
        (begin
            (set! cx (loword lp) cy(hiword lp))
            (setwindowtext hwnd 'wow')
            (set! hdc (getprinterdc) )
            (startdoc hdc)
            (startpage hdc)
            (set! cx (getdevicecaps hdc HORZRES))
            (set! cy (getdevicecaps hdc VERTRES))
            (pageprint hdc cx cy)
            (endpage hdc)
            (enddoc hdc)
            #t
        )
    ))    
    (define winproc         (lambda (hwnd msg wp lp )
        (begin
            (if (= WM_PAINT msg)(onpaint hwnd ))
            (if (= WM_CREATE msg)(oncreate hwnd msg wp lp) )
            (if (= WM_DESTROY msg)(quit) )
            (if (= WM_COMMAND msg)(setwindowtext hwnd (loword wp)) )
            (if (= WM_SYSCOMMAND msg)(if (= wp 1)(onprint hwnd msg wp lp) ))
            (if (= WM_SIZE msg)(onsize hwnd msg wp lp)) 
            (DefWindowProc hwnd msg wp lp )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)

#define MM_ISOTROPIC        7
#define MM_ANISOTROPIC      8
////MM_ISOTROPIC 各向同性的模式下，取得的Viewport Size和设置，通常是不同的。一遍保证横向纵向的比例正确。