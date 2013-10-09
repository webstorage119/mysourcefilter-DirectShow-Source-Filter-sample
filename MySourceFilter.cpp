#include"stdafx.h"

CMySource::CMySource(IUnknown *pUnk, HRESULT *phr) : 
	CSource(FILTER_NAME, pUnk, CLSID_MySource) 
{
	CPushPin *pPin = new CPushPin(phr, this);
	if(pPin==NULL) {
		*phr=E_OUTOFMEMORY;
	}
}

CMySource::~CMySource() {
}

CUnknown * WINAPI CMySource::CreateInstance(IUnknown *pUnk, HRESULT *phr) {
	CMySource *pNewFilter = new CMySource(pUnk, phr);
	if(pNewFilter == NULL) {
		*phr=E_OUTOFMEMORY;
	}
	return pNewFilter;
}
