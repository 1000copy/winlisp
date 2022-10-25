(begin
    (load '.\lib\constants.lsp')
    (define! msgboxID (MessageBox 0 'a' 'bcd' (orl MB_ICONWARNING  MB_CANCELTRYCONTINUE  MB_DEFBUTTON2  )))    
    (if (= msgboxID IDCANCEL)(MessageBox 0  'cancel' 'you select' MB_OK))
    (if (= msgboxID IDTRYAGAIN)(MessageBox 0  'retry' 'you select' MB_OK))
    (if (= msgboxID IDCONTINUE)(MessageBox 0  'continue' 'you select' MB_OK))
    (quit)
)
