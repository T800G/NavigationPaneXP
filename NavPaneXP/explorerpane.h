#ifndef _NAVPANE_CAE2EA7B_3A68_46D2_97F3_5EDD5F1A4F9F_
#define _NAVPANE_CAE2EA7B_3A68_46D2_97F3_5EDD5F1A4F9F_


//http://msdn.microsoft.com/en-us/library/windows/desktop/gg537746%28v=vs.85%29.aspx
#define CLSID_Favorites  L"{EFA24E61-B078-11D0-89E4-00C04FC9E26E}"
#define CLSID_History    L"{EFA24E62-B078-11D0-89E4-00C04FC9E26E}"
#define CLSID_Channels   L"{EFA24E63-B078-11D0-89E4-00C04FC9E26E}"
#define CLSID_Folders    L"{EFA24E64-B078-11D0-89E4-00C04FC9E26E}"
#define CLSID_Search     L"{30D02401-6A81-11d0-8274-00C04FD5AE38}"

//http://support.microsoft.com/kb/255920
inline HRESULT ShowBrowserBar(__in IWebBrowser2 *pWebBrowser2, __in OLECHAR* pszCLSID, __in BOOL bShow=TRUE)//VARIANT_BOOL
{
	_ASSERTE(pWebBrowser2);
	_ASSERTE(pszCLSID);
	HRESULT hr=E_FAIL;
	VARIANT vtBandGUID, vtShow;
	vtBandGUID.vt = VT_BSTR;
	vtBandGUID.bstrVal = SysAllocString(pszCLSID);
	if (vtBandGUID.bstrVal!=NULL)
	{
		vtShow.vt = VT_BOOL;
		vtShow.boolVal = (bShow ? VARIANT_TRUE : VARIANT_FALSE);
		hr=pWebBrowser2->ShowBrowserBar(&vtBandGUID, &vtShow, 0);
		SysFreeString(vtBandGUID.bstrVal);
	}
return hr;
}


inline HWND FindFavoritesPane(HWND hExplWnd)
{
	HWND hw=FindWindowEx(hExplWnd,NULL,_T("BaseBar"),NULL);
	if (hw)
	{
		ATLTRACE("BaseBar HWND==%x\n",hw);
		hw=FindWindowEx(hw,NULL,_T("ReBarWindow32"),NULL);
		if (hw)
		{
			ATLTRACE("ReBarWindow32 HWND==%x\n",hw);
			//get "Favorites" localized string window title
			TCHAR strbuf[256];
			if (0!=LoadString(GetModuleHandle(L"Shell32.dll"), 9106, strbuf, 255))
			{
				hw=FindWindowEx(hw,NULL,_T("SysTreeView32"), strbuf);
				return hw;
			}
		}
	}
return NULL;
}


inline HWND FindShellView(HWND hExplWnd)
{
	HWND hw=FindWindowEx(hExplWnd,NULL,_T("SHELLDLL_DefView"),NULL);
	if (hw)
	{
		//using classic folders
		ATLTRACE("SHELLDLL_DefView HWND==%x\n",hw);
		HWND lvhwnd=FindWindowEx(hw,NULL,_T("SysListView32"),NULL);
		if (lvhwnd)
		{
			ATLTRACE("SHELLDLL_DefView>>>SysListView32 HWND==%x\n",lvhwnd);
			return lvhwnd;
		}
		else
		{
			//web view enabled
			hw=FindWindowEx(hw,NULL,_T("DUIViewWndClassName"),NULL);
			if (hw)
			{
				ATLTRACE("DUIViewWndClassName HWND==%x\n",hw);
				hw=FindWindowEx(hw,NULL,_T("DirectUIHWND"),NULL);
				if (hw)
				{
					ATLTRACE("DUIViewWndClassName>>>DirectUIHWND HWND==%x\n",hw);
					hw=FindWindowEx(hw,NULL,_T("CtrlNotifySink"),NULL);
					if (hw)
					{
						ATLTRACE("DUIViewWndClassName>>>DirectUIHWND>>>CtrlNotifySink HWND==%x\n",hw);
						hw=FindWindowEx(hw,NULL,_T("SysListView32"),NULL);
						if (hw)
						{
							ATLTRACE("DUIViewWndClassName>>>DirectUIHWND>>>CtrlNotifySink>>>SysListView32 HWND==%x\n",hw);
							return hw;
						}				
					}				
				}			
			}		
		}
	}
return NULL;
}

#endif//_NAVPANE_CAE2EA7B_3A68_46D2_97F3_5EDD5F1A4F9F_
