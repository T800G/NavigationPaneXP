#ifndef _STDAFX_671C0DF9_8319_4342_9C72_39E1D5845B12_
#define _STDAFX_671C0DF9_8319_4342_9C72_39E1D5845B12_
#pragma once

#define _WIN32_WINNT  _WIN32_WINNT_WINXP

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

// C RunTime Header Files
#ifndef _ATL_MIN_CRT
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#endif

#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif



#endif//_STDAFX_671C0DF9_8319_4342_9C72_39E1D5845B12_
