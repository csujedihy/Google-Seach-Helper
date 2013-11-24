// TestScript.h : Declaration of the CTestScript

#pragma once
#include "resource.h"       // main symbols

#include "TestBHO_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CTestScript

class ATL_NO_VTABLE CTestScript :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestScript, &CLSID_TestScript>,
	public IObjectWithSiteImpl<CTestScript>,
	public IDispatchImpl<ITestScript, &IID_ITestScript, &LIBID_TestBHOLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<1, CTestScript, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>,
	//public IPersistPropertyBagImpl<CTestScript>,
public IObjectSafetyImpl<CTestScript, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CTestScript()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTSCRIPT)

DECLARE_NOT_AGGREGATABLE(CTestScript)

BEGIN_COM_MAP(CTestScript)
	COM_INTERFACE_ENTRY(ITestScript)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	BEGIN_SINK_MAP(CTestScript)
		SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)
		SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, onBeforeNavigate2)
	END_SINK_MAP()
	bool isMainFrame(IDispatch *pDisp);
	void STDMETHODCALLTYPE OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL);
	void STDMETHODCALLTYPE onBeforeNavigate2(IDispatch *pDisp, VARIANT *vUrl, VARIANT *Flags, VARIANT *TargetFrameName, VARIANT *PostData, VARIANT *Headers, VARIANT_BOOL *Cancel);
	//void STDMETHODCALLTYPE OnNavigationComplete(IDispatch *pDisp, VARIANT *pvarURL);

	STDMETHOD(SetSite)(IUnknown *pUnkSite);

	HRESULT STDMETHODCALLTYPE DoSomething(){
		::MessageBox(NULL, L"Hello", L"World", MB_OK);
		return S_OK;
	}
public:
	
//private:
	// InstallBHOMethod();

private:
	CComBSTR m_currenturl;
	CComPtr<IWebBrowser2>  m_spWebBrowser;
	BOOL m_fAdvised;
};

OBJECT_ENTRY_AUTO(__uuidof(TestScript), CTestScript)
