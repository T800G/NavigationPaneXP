// ExplorerBHO.cpp : Implementation of CNavpanexpApp and DLL registration.

#include "stdafx.h"
#include "ExplorerBHO.h"

#include "explorerpane.h"

/////////////////////////////////////////////////////////////////////////////
//

HRESULT CExplorerBHO::FinalConstruct()
{
	//don't load BHO in IE6/7/8
	TCHAR szExePath[MAX_PATH];
	if (!GetModuleFileName(NULL, szExePath, MAX_PATH)) return HRESULT_FROM_WIN32(GetLastError());
	if (StrCmpI(PathFindFileName(szExePath), _T("iexplore.exe"))==0) return E_ABORT;

return S_OK;
}

void CExplorerBHO::FinalRelease()
{
	ATLTRACE("CExplorerBHO::FinalRelease\n");
}

HRESULT CExplorerBHO::SetSite(IUnknown *pUnkSite)
{
	IObjectWithSiteImpl<CExplorerBHO>::SetSite(pUnkSite);

	if(pUnkSite)
	{
		LoadSettings(&m_dwSettings);//settings apply on every new window/site

		CComPtr<IServiceProvider> psp;
		if SUCCEEDED(pUnkSite->QueryInterface(IID_IServiceProvider,(void**)&psp))
		{
			if SUCCEEDED(psp->QueryService(SID_SWebBrowserApp, IID_IWebBrowser2, (void**)&m_pWebBrowser2))
			{
				if (m_dwSettings & OPT_FAVPANE) ShowBrowserBar(m_pWebBrowser2, CLSID_Favorites, TRUE);
				if (m_dwSettings & OPT_FLDRPANE) ShowBrowserBar(m_pWebBrowser2, CLSID_Folders, TRUE);

				if (m_dwEventCookie==0xFEFEFEFE)
					DispEventAdvise(m_pWebBrowser2, &IID_IDispatch);
			}
		}
	}
	else
	{
		ATLTRACE("CExplorerBHO::SetSite(NULL)\n");
		OnQuit();
		m_pWebBrowser2.Release();
	}
return S_OK;
}

void CExplorerBHO::OnQuit()
{
	//ATLTRACE("CExplorerBHO::OnQuit\n");
	ATLASSERT(m_pWebBrowser2);
	if(m_pWebBrowser2 && (m_dwEventCookie!=0xFEFEFEFE))
		DispEventUnadvise(m_pWebBrowser2, &DIID_DWebBrowserEvents2);
}


void CExplorerBHO::OnDocumentComplete(IDispatch *pDisp, VARIANT *URL)
{
	//ATLTRACE("CExplorerBHO::OnDocumentComplete\n");
	ATLASSERT(m_pWebBrowser2);
	if (m_dwSettings & OPT_FOCUS)
	{
		SHANDLE_PTR hExplWnd;
		if (S_OK==m_pWebBrowser2->get_HWND(&hExplWnd))
		{
			HWND hw=FindShellView((HWND)hExplWnd);
			if (hw!=NULL)
			{
				ATLTRACE(_T("FindShellView HWND==%x\n"),hw);
				//not focused, no modifier key pressed
				if ((GetFocus()!=hw) && !(GetAsyncKeyState(VK_SHIFT)<0))
					SetFocus(hw);
			}
		}	
	}
}
