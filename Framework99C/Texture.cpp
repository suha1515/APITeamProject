#include "stdafx.h"
#include "Texture.h"


CTexture::CTexture()
	:m_hMemDC(NULL), nTextureRef(0)
{
	m_bColorKeyEnable = true;
	m_tColorKey = RGB(255, 0, 255);
	AddRef();
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
	const TCHAR* pPath = CPathMgr::GetInstance()->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	if(!m_hBitmap)
		m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap); // Q.매번 출력전에 선택해줘야되는거같은데이유는?!
	GetObject(m_hBitmap, sizeof(BITMAP), &m_tBit);
	return true;
}

void CTexture::AddRef()
{
	nTextureRef++;
}

void CTexture::SafeDelete()
{
	nTextureRef--;
	if (0 == nTextureRef)
	{
		delete this;
	}
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

void CTexture::DrawTexture(HDC hDC, IMGINFO& imgInfo)
{
	if (m_bColorKeyEnable)
	{
		TransparentBlt(hDC, imgInfo.fX - (imgInfo.fImgCX * imgInfo.fPivotX), imgInfo.fY - (imgInfo.fImgCY * imgInfo.fPivotY),
			imgInfo.fImgCX, imgInfo.fImgCY, m_hMemDC, 0, 0, m_tBit.bmWidth / maxX , m_tBit.bmHeight, m_tColorKey);
	}
	else
	{
		BitBlt(hDC, imgInfo.fX - (imgInfo.fImgCX * imgInfo.fPivotX), imgInfo.fY - (imgInfo.fImgCY * imgInfo.fPivotY),
			imgInfo.fImgCX, imgInfo.fImgCY, m_hMemDC, imgInfo.fX, imgInfo.fY, SRCCOPY);
				//BitBlt(hDC, 0,0,WINCX,WINCY,m_hMemDC, 0, imgInfo.fY, SRCCOPY);
	}
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_tColorKey = colorKey;
}

void CTexture::SetKeyEnable(bool keyEnable)
{
	m_bColorKeyEnable = keyEnable;
}


HDC CTexture::GetDC()
{
	return m_hMemDC;
}