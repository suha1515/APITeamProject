#include "stdafx.h"
#include "Texture.h"


CTexture::CTexture()
	:m_hMemDC(NULL)
{
	m_bColorKeyEnable = false;
	m_tColorKey = RGB(255, 0, 255);
}


CTexture::~CTexture()
{
	m_hBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}


bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const string & strKey, const TCHAR * pFileName, const string & strPathKey)
{
	if(!m_hMemDC)
		m_hMemDC = CreateCompatibleDC(hDC);

	// 전체 경로
	const TCHAR* pPath = CPathMgr::FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	if(!m_hBitmap)
		m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return true;
}

BITMAP CTexture::GetBitmap()
{
	return m_tBit;
}

bool CTexture::GetKeyEnable()
{
	return m_bColorKeyEnable;
}

COLORREF CTexture::GetColorKey()
{
	return m_tColorKey;
}

void CTexture::Render(HDC hDC)
{
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap); // Q.매번 출력전에 선택해줘야되는거같은데이유는?!
	GetObject(m_hBitmap, sizeof(BITMAP), &m_tBit);
}

void CTexture::SetPivot(INFO pivot)
{
	m_tPivot = pivot;
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_tColorKey = colorKey;
}

HDC CTexture::GetDC()
{
	return m_hMemDC;
}