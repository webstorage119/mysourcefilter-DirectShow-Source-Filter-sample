#pragma once

#define TEMPLATE_NAME	(L"My Source Filter")
#define FILTER_NAME		(TEMPLATE_NAME)
#define OUTPUT_PIN_NAME (L"Output")

// {78A3788B-F360-45f9-8E1D-443D3C63BD0B}
DEFINE_GUID(CLSID_MySource, 
			0x78a3788b, 0xf360, 0x45f9, 0x8e, 0x1d, 0x44, 0x3d, 0x3c, 0x63, 0xbd, 0xb);

// ピンタイプの定義
const AMOVIESETUP_MEDIATYPE sudPinTypes =
{
	&MEDIATYPE_Video,
	&MEDIASUBTYPE_RGB32
};
// 入力用、出力用ピンの情報
const AMOVIESETUP_PIN sudPins =
{
	OUTPUT_PIN_NAME,
	FALSE,
	TRUE,
	FALSE,
	FALSE,
	&CLSID_NULL,
	NULL,
	1,
	&sudPinTypes
};

// フィルタ情報
const AMOVIESETUP_FILTER afFilterInfo=
{
	&CLSID_MySource,
	FILTER_NAME,
	MERIT_DO_NOT_USE,
	1,
	&sudPins
};

// ソースフィルタクラス
class CMySource : CSource {
public:
	CMySource(LPUNKNOWN pUnk, HRESULT *phr);
	virtual ~CMySource();
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN pUnk, HRESULT *phr);
protected:
private:
};

// プッシュピンクラス
class CPushPin : CSourceStream {
public:
	CPushPin(HRESULT *phr, CSource *pFilter);
	virtual			~CPushPin();
	STDMETHODIMP	Notify(IBaseFilter *pSelf, Quality q);
	// CSourceStreamの実装
	HRESULT			GetMediaType(CMediaType *pMediaType);
	HRESULT			CheckMediaType(const CMediaType *pMediaType);
	HRESULT			DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pRequest);
	HRESULT			FillBuffer(IMediaSample *pSample);
protected:
private:
	CSource*		m_pFilter;			//このピンが所属しているフィルタへのポインタ
	unsigned __int64 m_Count;			//フレームカウンタ

	REFERENCE_TIME	m_rtFrameLength;	//1フレームあたりの時間

	HBITMAP m_Bitmap;
	LPDWORD m_BmpData;
	HDC     m_Hdc;
};
