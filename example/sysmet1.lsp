(begin
    (load '.\lib\constants.lsp')
    (def!  texts(
            (SM_CXSCREEN 'SM_CXSCREEN' 'Screen width in pixels')
            (SM_CYSCREEN 'SM_CYSCREEN' 'Screen height in pixels')
            (SM_CXVSCROLL             'SM_CXVSCROLL'               'Vertical scroll width')            
            (SM_CYHSCROLL             'SM_CYHSCROLL'               'Horizontal scroll height')
            (SM_CYCAPTION             'SM_CYCAPTION'               'Caption bar height')
            (SM_CXBORDER              'SM_CXBORDER'                'Window border width')
            (SM_CYBORDER              'SM_CYBORDER'                'Window border height')
            (SM_CXFIXEDFRAME          'SM_CXFIXEDFRAME'            'Dialog window frame width')
            (SM_CYFIXEDFRAME          'SM_CYFIXEDFRAME'            'Dialog window frame height')
            (SM_CYVTHUMB              'SM_CYVTHUMB'                'Vertical scroll thumb height')
            (SM_CXHTHUMB              'SM_CXHTHUMB'                'Horizontal scroll thumb width')
            (SM_CXICON                'SM_CXICON'                  'Icon width')
            (SM_CYICON                'SM_CYICON'                  'Icon height')
            (SM_CXCURSOR              'SM_CXCURSOR'                'Cursor width')
            (SM_CYCURSOR              'SM_CYCURSOR'                'Cursor height')
            (SM_CYMENU                'SM_CYMENU'                  'Menu bar height')
            (SM_CXFULLSCREEN          'SM_CXFULLSCREEN'            'Full screen client area width')
            (SM_CYFULLSCREEN          'SM_CYFULLSCREEN'            'Full screen client area height')
            (SM_CYKANJIWINDOW         'SM_CYKANJIWINDOW'           'Kanji window height')
            (SM_MOUSEPRESENT          'SM_MOUSEPRESENT'            'Mouse present flag')
            (SM_CYVSCROLL             'SM_CYVSCROLL'               'Vertical scroll arrow height')
            (SM_CXHSCROLL             'SM_CXHSCROLL'               'Horizontal scroll arrow width')
            (SM_DEBUG                 'SM_DEBUG'                   'Debug version flag')
            (SM_SWAPBUTTON            'SM_SWAPBUTTON'              'Mouse buttons swapped flag')
            (SM_CXMIN                 'SM_CXMIN'                   'Minimum window width')
            (SM_CYMIN                 'SM_CYMIN'                   'Minimum window height')
            (SM_CXSIZE                'SM_CXSIZE'                  'Min/Max/Close button width')
            (SM_CYSIZE                'SM_CYSIZE'                  'Min/Max/Close button height')
            (SM_CXSIZEFRAME           'SM_CXSIZEFRAME'             'Window sizing frame width')
            (SM_CYSIZEFRAME           'SM_CYSIZEFRAME'             'Window sizing frame height')
            (SM_CXMINTRACK            'SM_CXMINTRACK'              'Minimum window tracking width')
            (SM_CYMINTRACK            'SM_CYMINTRACK'              'Minimum window tracking height')
            (SM_CXDOUBLECLK           'SM_CXDOUBLECLK'             'Double click x tolerance')
            (SM_CYDOUBLECLK           'SM_CYDOUBLECLK'             'Double click y tolerance')
            (SM_CXICONSPACING         'SM_CXICONSPACING'               'Horizontal icon spacing')
            (SM_CYICONSPACING         'SM_CYICONSPACING'               'Vertical icon spacing')
            (SM_MENUDROPALIGNMENT     'SM_MENUDROPALIGNMENT'               'Left or right menu drop')
            (SM_PENWINDOWS            'SM_PENWINDOWS'              'Pen extensions installed')
            (SM_DBCSENABLED           'SM_DBCSENABLED'             'Double-Byte Char Set enabled')
            (SM_CMOUSEBUTTONS         'SM_CMOUSEBUTTONS'               'Number of mouse buttons')
            (SM_SECURE                'SM_SECURE'              'Security present flag')
            (SM_CXEDGE                'SM_CXEDGE'              '3-D border width')
            (SM_CYEDGE                'SM_CYEDGE'              '3-D border height')
            (SM_CXMINSPACING          'SM_CXMINSPACING'            'Minimized window spacing width')
            (SM_CYMINSPACING          'SM_CYMINSPACING'            'Minimized window spacing height')
            (SM_CXSMICON              'SM_CXSMICON'            'Small icon width')
            (SM_CYSMICON              'SM_CYSMICON'            'Small icon height')
            (SM_CYSMCAPTION           'SM_CYSMCAPTION'             'Small caption height')
            (SM_CXSMSIZE              'SM_CXSMSIZE'            'Small caption button width')
            (SM_CYSMSIZE              'SM_CYSMSIZE'            'Small caption button height')
            (SM_CXMENUSIZE            'SM_CXMENUSIZE'              'Menu bar button width')
            (SM_CYMENUSIZE            'SM_CYMENUSIZE'              'Menu bar button height')
            (SM_ARRANGE               'SM_ARRANGE'             'How minimized windows arranged')
            (SM_CXMINIMIZED           'SM_CXMINIMIZED'             'Minimized window width')
            (SM_CYMINIMIZED           'SM_CYMINIMIZED'             'Minimized window height')
            (SM_CXMAXTRACK            'SM_CXMAXTRACK'              'Maximum draggable width')
            (SM_CYMAXTRACK            'SM_CYMAXTRACK'              'Maximum draggable height')
            (SM_CXMAXIMIZED           'SM_CXMAXIMIZED'             'Width of maximized window')
            (SM_CYMAXIMIZED           'SM_CYMAXIMIZED'             'Height of maximized window')
            (SM_NETWORK               'SM_NETWORK'             'Network present flag')
            (SM_CLEANBOOT             'SM_CLEANBOOT'               'How system was booted')
            (SM_CXDRAG                'SM_CXDRAG'              'Avoid drag x tolerance')
            (SM_CYDRAG                'SM_CYDRAG'              'Avoid drag y tolerance')
            (SM_SHOWSOUNDS            'SM_SHOWSOUNDS'              'Present sounds visually')
            (SM_CXMENUCHECK           'SM_CXMENUCHECK'             'Menu check-mark width')
            (SM_CYMENUCHECK           'SM_CYMENUCHECK'             'Menu check-mark height')
            (SM_SLOWMACHINE           'SM_SLOWMACHINE'             'Slow processor flag')
            (SM_MIDEASTENABLED        'SM_MIDEASTENABLED'              'Hebrew and Arabic enabled flag')
            (SM_MOUSEWHEELPRESENT     'SM_MOUSEWHEELPRESENT'               'Mouse wheel present flag')
            (SM_XVIRTUALSCREEN        'SM_XVIRTUALSCREEN'              'Virtual screen x origin')
            (SM_YVIRTUALSCREEN        'SM_YVIRTUALSCREEN'              'Virtual screen y origin')
            (SM_CXVIRTUALSCREEN       'SM_CXVIRTUALSCREEN'             'Virtual screen width')
            (SM_CYVIRTUALSCREEN       'SM_CYVIRTUALSCREEN'             'Virtual screen height')
            (SM_CMONITORS             'SM_CMONITORS'               'Number of monitors')
            (SM_SAMEDISPLAYFORMAT     'SM_SAMEDISPLAYFORMAT'               'Same color format flag')            
    ))
    (define oncreate (lambda (hwnd )        
        (begin
            (def rect(getclientrect hwnd))
            (def hlistview(lv_create hwnd rect))
            (lv_setcolumns hlistview (list 'id' 'name' 'comment') (list 200 150 250))
            (def i 0 id 0 c1 0 c2 0)
            (repeat (length texts)(begin
                (set! id (getsystemmetrics (nth (nth texts i)0)))
                (set! c1 (nth (nth texts i)1))
                (set! c2 (nth (nth texts i)2))
                (lv_appenditem hlistview (+ i 1)(list  c1 id c2))
                (set! i(+ i 1))
            ))
            #t
        )
    ))
    (define winproc (lambda (hwnd msg wp lp)
        (begin
            (if (= WM_CREATE msg)(oncreate hwnd))
            (if (= WM_DESTROY msg)(quit) )
            (DefWindowProc hwnd msg wp lp )
        )                
    ))
    (register (app) 'HelloWin1' )
    (create (app) 'HelloWin1')
)