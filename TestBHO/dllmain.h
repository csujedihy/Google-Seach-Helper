// dllmain.h : Declaration of module class.

class CTestBHOModule : public CAtlDllModuleT< CTestBHOModule >
{
public :
	DECLARE_LIBID(LIBID_TestBHOLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTBHO, "{1C6F51F8-BCE6-4702-8952-6A8233359FBC}")
};

extern class CTestBHOModule _AtlModule;
