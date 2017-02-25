#ifndef _EXPLORERBHO_DB7458A7_5307_4E24_A129_7B0FE579BAF9_
#define _EXPLORERBHO_DB7458A7_5307_4E24_A129_7B0FE579BAF9_

#include "resource.h"       // main symbols
#include "settings.h"
#include "navpanexp.h"//MIDL generated

#include <shlobj.h>
#include <comdef.h>
#include <shobjidl.h>
#include <shlguid.h>
#include <exdispid.h>
#pragma comment(lib,"atlthunk.lib") //resolves LNK2019 'missing CComStdCallThunkHelper()' for x64 build


class ATL_NO_VTABLE CExplorerBHO : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExplorerBHO, &CLSID_ExplorerBHO>,
	public IObjectWithSiteImpl<CExplorerBHO>,
	public IDispatchImpl<IExplorerBHO, &IID_IExplorerBHO, &LIBID_NAVPANEXPLib,/*wMajor =*/ 1 /*,wMinor = 0*/ >,
	public IDispEventImpl<1, CExplorerBHO, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1,1>
{
public:
	CExplorerBHO(): m_dwSettings(OPT_DEFAULTSETTINGS) {}
	//virtual ~CExplorerBHO() {}

	BEGIN_COM_MAP(CExplorerBHO)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	BEGIN_SINK_MAP( CExplorerBHO )
		SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_ONQUIT, OnQuit)
		SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)
	END_SINK_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_ExplorerBHO)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

	//IObjectWithSite override
	STDMETHOD(SetSite)(IUnknown *pUnkSite);

	//IDispEventImpl
	STDMETHOD_(void, OnQuit)(void);
	STDMETHOD_(void, OnDocumentComplete)(IDispatch*, VARIANT*);

private:
	CComPtr<IWebBrowser2> m_pWebBrowser2;
	DWORD m_dwSettings;
};

#endif//_EXPLORERBHO_DB7458A7_5307_4E24_A129_7B0FE579BAF9_
