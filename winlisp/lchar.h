#pragma once
#ifdef _UNICODE
#define __STR LPWSTR 
#define __CSTR LPCWSTR 
#define __STDSTR std::wstring
#else
#define __STR LPSTR 
#define __CSTR LPCSTR 
#define __STDSTR std::string
#endif
