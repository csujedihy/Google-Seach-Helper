// TestScript.cpp : Implementation of CTestScript

#include "stdafx.h"
#include "TestScript.h"
#include <string>
#include "Util.h"

using namespace std;
// CTestScript
void debug(LPWSTR msg)
{
	::MessageBox(NULL,msg,L"Debug",MB_OK);;
}

STDMETHODIMP CTestScript::SetSite(IUnknown* pUnkSite)
{
	if (pUnkSite != NULL)
	{
		HRESULT hr = pUnkSite->QueryInterface(IID_IWebBrowser2, (void **)&m_spWebBrowser);
		if (SUCCEEDED(hr))
		{
			hr = DispEventAdvise(m_spWebBrowser);
			if (SUCCEEDED(hr))
			{
				m_fAdvised = TRUE;				
			}
		}
	}else
	{
		if (m_fAdvised)
		{
			DispEventUnadvise(m_spWebBrowser);
			m_fAdvised = FALSE;
		}
		m_spWebBrowser.Release();
	}
	return IObjectWithSiteImpl<CTestScript>::SetSite(pUnkSite);
}

bool CTestScript::isMainFrame(IDispatch *pDisp){
	CComQIPtr<IWebBrowser2> spTempWebBrowser = pDisp;
	if (spTempWebBrowser && m_spWebBrowser && m_spWebBrowser.IsEqualObject(spTempWebBrowser))
		return true;
	return false;
}

void STDMETHODCALLTYPE CTestScript::onBeforeNavigate2(IDispatch *pDisp, VARIANT *vUrl, VARIANT *Flags, VARIANT *TargetFrameName, VARIANT *PostData, VARIANT *Headers, VARIANT_BOOL *Cancel)
{
	
	if(isMainFrame(pDisp)){
		USES_CONVERSION;
		char *gchara[] ={"www.google","q="};
		char *pchara[] ={"www.google","url="};
		char* urlstr = OLE2A(m_currenturl);
		char* purl =OLE2A(vUrl->bstrVal);
		ATLTRACE("now url=%s",purl);
		map<string,string> param;
			if(strstr(purl,pchara[0])&&strstr(purl,pchara[1])){
			Util::param_in_url(purl,param);
			string decodedUrl = Util::deescapeURL(param["url"]);
			ATLTRACE("url=%s",param["url"].c_str());
			ATLTRACE("decodedURL=%s",decodedUrl.c_str());
			CComBSTR redirect2url(decodedUrl.c_str());
			CComVariant vredirect2url(decodedUrl.c_str());
			ATLTRACE("decodedURL=%S",redirect2url);
			m_spWebBrowser->Navigate2(&vredirect2url,Flags,TargetFrameName,PostData,Headers);
			m_spWebBrowser->put_Visible(VARIANT_TRUE);
	
			}
		ATLTRACE("b4Navi!");
	
	
	}

}




void STDMETHODCALLTYPE CTestScript::OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL)
{
	if(isMainFrame(pDisp)){
		ATLTRACE2("DocComplete!");
		m_spWebBrowser->get_LocationURL(&m_currenturl);
	}
}

