#include "stdafx.h"

#define LOGING_LEVEL 5

extern "C" {
	BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);
};

CFactoryTemplate g_Templates [] = {
	{ TEMPLATE_NAME , &CLSID_MySource, CMySource::CreateInstance, NULL, &afFilterInfo}
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);


STDAPI DllRegisterServer() {
	return AMovieDllRegisterServer2(TRUE);
}

STDAPI DllUnregisterServer() {
	return AMovieDllRegisterServer2(FALSE);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  dwReason, LPVOID lpReserved) {
	DbgSetModuleLevel(LOG_TRACE,LOGING_LEVEL);
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}
