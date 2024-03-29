(begin    
    (def 
        HORZRES       8   
        VERTRES       10 
    )
    (def    WM_CHAR 258 WM_CHAR 0x0102
            WM_COMMAND          0x0111
            WM_SYSCOMMAND       0x0112
    )
    (def 
         MF_INSERT           0x00000000
         MF_CHANGE           0x00000080
         MF_APPEND           0x00000100
         MF_DELETE           0x00000200
         MF_REMOVE           0x00001000

         MF_BYCOMMAND        0x00000000
         MF_BYPOSITION       0x00000400

         MF_SEPARATOR        0x00000800

         MF_ENABLED          0x00000000
         MF_GRAYED           0x00000001
         MF_DISABLED         0x00000002

         MF_UNCHECKED        0x00000000
         MF_CHECKED          0x00000008
         MF_USECHECKBITMAPS  0x00000200

         MF_STRING           0x00000000
         MF_BITMAP           0x00000004
         MF_OWNERDRAW        0x00000100

         MF_POPUP            0x00000010
         MF_MENUBARBREAK     0x00000020
         MF_MENUBREAK        0x00000040

         MF_UNHILITE         0x00000000
         MF_HILITE           0x00000080
    )
    (def 
        WM_MOUSEMOVE                    0x0200
        WM_LBUTTONDOWN                  0x0201
        WM_LBUTTONUP                    0x0202
        WM_LBUTTONDBLCLK                0x0203
        WM_RBUTTONDOWN                  0x0204
        WM_RBUTTONUP                    0x0205
        WM_RBUTTONDBLCLK                0x0206
        WM_MBUTTONDOWN                  0x0207
        WM_MBUTTONUP                    0x0208
        WM_MBUTTONDBLCLK                0x0209
    )
    (def 
        LBN_ERRSPACE        -2
        LBN_SELCHANGE       1
        LBN_DBLCLK          2
        LBN_SELCANCEL       3
        LBN_SETFOCUS        4
        LBN_KILLFOCUS       5
    )
    (quote Button Notifier)    

    (# Button Notifier)
    (def 
            BN_CLICKED          0
            BN_PAINT            1
            BN_HILITE           2
            BN_UNHILITE         3
            BN_DISABLE          4
            BN_DOUBLECLICKED    5
            BN_PUSHED           BN_HILITE
            BN_UNPUSHED         BN_UNHILITE
            BN_DBLCLK           BN_DOUBLECLICKED
            BN_SETFOCUS         6
            BN_KILLFOCUS        7)        
    (def    BS_PUSHBUTTON       0x00000000
            BS_DEFPUSHBUTTON    0x00000001
            BS_CHECKBOX         0x00000002
            BS_AUTOCHECKBOX     0x00000003
            BS_RADIOBUTTON      0x00000004
            BS_3STATE           0x00000005
            BS_AUTO3STATE       0x00000006
            BS_GROUPBOX         0x00000007
            BS_USERBUTTON       0x00000008
            BS_AUTORADIOBUTTON  0x00000009
            BS_PUSHBOX          0x0000000A
            BS_OWNERDRAW        0x0000000B)
    (define 
        WM_CREATE   1
        WM_PAINT    15
        WM_DESTROY  2
        WM_MOVE                         0x0003
        WM_SIZE                         0x0005)  
    (def 
        MM_ANISOTROPIC      8 
        MM_TEXT             1
        MM_LOMETRIC         2
        MM_HIMETRIC         3
        MM_LOENGLISH        4
        MM_HIENGLISH        5
        MM_TWIPS            6
        MM_ISOTROPIC        7)
    (# System Metrics)
    (def 
        SM_CXSCREEN             0   
        SM_CYSCREEN             1
        SM_CXVSCROLL            2
        SM_CYHSCROLL            3
        SM_CYCAPTION            4
        SM_CXBORDER             5
        SM_CYBORDER             6
        SM_CXDLGFRAME           7
        SM_CYDLGFRAME           8
        SM_CYVTHUMB             9
        SM_CXHTHUMB             10
        SM_CXICON               11
        SM_CYICON               12
        SM_CXCURSOR             13
        SM_CYCURSOR             14
        SM_CYMENU               15
        SM_CXFULLSCREEN         16
        SM_CYFULLSCREEN         17
        SM_CYKANJIWINDOW        18
        SM_MOUSEPRESENT         19
        SM_CYVSCROLL            20
        SM_CXHSCROLL            21
        SM_DEBUG                22
        SM_SWAPBUTTON           23
        SM_RESERVED1            24
        SM_RESERVED2            25
        SM_RESERVED3            26
        SM_RESERVED4            27
        SM_CXMIN                28
        SM_CYMIN                29
        SM_CXSIZE               30
        SM_CYSIZE               31
        SM_CXFRAME              32
        SM_CYFRAME              33
        SM_CXMINTRACK           34
        SM_CYMINTRACK           35
        SM_CXDOUBLECLK          36
        SM_CYDOUBLECLK          37
        SM_CXICONSPACING        38
        SM_CYICONSPACING        39
        SM_MENUDROPALIGNMENT    40
        SM_PENWINDOWS           41
        SM_DBCSENABLED          42
        SM_CMOUSEBUTTONS        43    
        SM_CXFIXEDFRAME           SM_CXDLGFRAME
        SM_CYFIXEDFRAME           SM_CYDLGFRAME
        SM_CXSIZEFRAME            SM_CXFRAME   
        SM_CYSIZEFRAME            SM_CYFRAME       
        SM_SECURE               44
        SM_CXEDGE               45
        SM_CYEDGE               46
        SM_CXMINSPACING         47
        SM_CYMINSPACING         48
        SM_CXSMICON             49
        SM_CYSMICON             50
        SM_CYSMCAPTION          51
        SM_CXSMSIZE             52
        SM_CYSMSIZE             53
        SM_CXMENUSIZE           54
        SM_CYMENUSIZE           55
        SM_ARRANGE              56
        SM_CXMINIMIZED          57
        SM_CYMINIMIZED          58
        SM_CXMAXTRACK           59
        SM_CYMAXTRACK           60
        SM_CXMAXIMIZED          61
        SM_CYMAXIMIZED          62
        SM_NETWORK              63
        SM_CLEANBOOT            67
        SM_CXDRAG               68
        SM_CYDRAG               69
        SM_SHOWSOUNDS           70
        SM_CXMENUCHECK          71 
        SM_CYMENUCHECK          72
        SM_SLOWMACHINE          73
        SM_MIDEASTENABLED       74
        SM_MOUSEWHEELPRESENT    75    
        SM_XVIRTUALSCREEN       76
        SM_YVIRTUALSCREEN       77
        SM_CXVIRTUALSCREEN      78
        SM_CYVIRTUALSCREEN      79
        SM_CMONITORS            80
        SM_SAMEDISPLAYFORMAT    81
        SM_IMMENABLED           82    
        SM_CXFOCUSBORDER        83
        SM_CYFOCUSBORDER        84    
        SM_TABLETPC             86
        SM_MEDIACENTER          87
        SM_STARTER              88
        SM_SERVERR2             89
        SM_MOUSEHORIZONTALWHEELPRESENT    91
        SM_CXPADDEDBORDER       92    
        SM_DIGITIZER            94
        SM_MAXIMUMTOUCHES       95
        SM_CMETRICS             76
        SM_CMETRICS             83
        SM_CMETRICS             91
        SM_CMETRICS             93
        SM_CMETRICS             97        
        SM_REMOTESESSION        0x1000        
        SM_SHUTTINGDOWN           0x2000   
        SM_REMOTECONTROL          0x2001
        SM_CARETBLINKINGENABLED   0x2002
        SM_CONVERTIBLESLATEMODE   0x2003
        SM_SYSTEMDOCKED           0x2004
    )
     (define!
        MB_OK                       0x00000000 
        MB_OKCANCEL                 0x00000001 
        MB_ABORTRETRYIGNORE         0x00000002 
        MB_YESNOCANCEL              0x00000003 
        MB_YESNO                    0x00000004 
        MB_RETRYCANCEL              0x00000005 
        MB_CANCELTRYCONTINUE        0x00000006 
        MB_ICONHAND                 0x00000010 
        MB_ICONQUESTION             0x00000020 
        MB_ICONEXCLAMATION          0x00000030 
        MB_ICONASTERISK             0x00000040 
        MB_USERICON                 0x00000080 
        MB_ICONWARNING              MB_ICONEXCLAMATION
        MB_ICONERROR                MB_ICONHAND
        MB_ICONINFORMATION          MB_ICONASTERISK
        MB_ICONSTOP                 MB_ICONHAND
        MB_DEFBUTTON1               0x00000000 
        MB_DEFBUTTON2               0x00000100 
        MB_DEFBUTTON3               0x00000200 
        MB_DEFBUTTON4               0x00000300 

        MB_APPLMODAL                0x00000000 
        MB_SYSTEMMODAL              0x00001000 
        MB_TASKMODAL                0x00002000 
        MB_HELP                     0x00004000 

        MB_NOFOCUS                  0x00008000 
        MB_SETFOREGROUND            0x00010000 
        MB_DEFAULT_DESKTOP_ONLY     0x00020000 

        MB_TOPMOST                  0x00040000 
        MB_RIGHT                    0x00080000 
        MB_RTLREADING               0x00100000 
        MB_SERVICE_NOTIFICATION          0x00200000 
        MB_SERVICE_NOTIFICATION          0x00040000 
        MB_SERVICE_NOTIFICATION_NT3X     0x00040000 

        MB_TYPEMASK                 0x0000000F 
        MB_ICONMASK                 0x000000F0 
        MB_DEFMASK                  0x00000F00 
        MB_MODEMASK                 0x00003000 
        MB_MISCMASK                 0x0000C000 
    )
    (define!        IDOK                1
        IDCANCEL            2
        IDABORT             3
        IDRETRY             4
        IDIGNORE            5
        IDYES               6
        IDNO                7
        IDCLOSE         8
        IDHELP          9
        IDTRYAGAIN      10
        IDCONTINUE      11
        IDTIMEOUT 32000
    )
) 
HEX NUMBER support 258 0x0102 WM_CHAR