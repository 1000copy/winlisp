"# winlisp" 

WinLisp is a LISP implementation with C++ on Microsoft Windows-64bit,which is backed with Win32 API,made it easy to Win32 programming .

A sample code which written by WinLisp ,like Charles Petzold's hello window ,is :

        (begin
            (# comment on 2022-10-14 by Reco)
            (load '.\lib\constants.lsp')
            (def onpaint(lambda (hwnd )
                (begin
                    (def triple (beginpaint hwnd ))
                    (def rect(getclientrect hwnd ))
                    (def hdc (nth triple 2))
                    (drawtext hdc 'hello,world!' rect)         
                    (endpaint  triple)
                    #t
                )
            ))
            (define handled (lambda (msg)(or (= WM_PAINT msg) (= WM_DESTROY msg))))
            (define winproc         (lambda (hwnd msg wp lp )
                (begin
                    (if (= WM_PAINT msg)(onpaint hwnd ))
                    (if (= WM_DESTROY msg)(quit) )
                    (if (not (handled msg)) (DefWindowProc hwnd msg wp lp ) 0)
                )                
            ))
            (register (app) 'HelloWin' )
            (create (app) 'HelloWin')
        )

more exapmle code see `example\`.

## BUILD

required Visual Studio 2022 with  std::c++20 

## known bugs

When the window is maximized, the previously centered text should be displayed in the new position and the text in the original position should disappear, but it doesn't.

## history 2022-10-14

When adjusting the generated configuration from debug to release, instead normal compilation, 3 errors occurred. The solution was to modify the configuration to match release config.

    <PropertyGroup>
        <CharacterSet>Unicode</CharacterSet>
        <CharacterSet>NotSet</CharacterSet>
    </PropertyGroup>
    <Link>
        <SubSystem>Console</SubSystem>
        <SubSystem>Windows</SubSystem>
    </Link>

One final issue is that the language needs to be adjusted to std::c++20
