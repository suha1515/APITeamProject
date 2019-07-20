#include "stdafx.h"
#include "Texture.h"


CTexture::CTexture()
{
	m_hDC = g_hDC;
}


CTexture::~CTexture()
{
	m_hBitmap = (HBITMAP)SelectObject(m_hDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

void CTexture::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, m_tPivot.fY, SRCCOPY);
}

bool CTexture::SetTexture(HINSTANCE _hInst, wstring _strPath, wstring _strFileName)
{

	if (!m_hMemDC)
	{
		m_hBitmap = (HBITMAP)LoadImage(_hInst, (_strPath + _strFileName).c_str(), IMAGE_BITMAP, 700, 8030, LR_LOADFROMFILE);
		m_hMemDC = CreateCompatibleDC(m_hDC);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
		GetObject(m_hBitmap, sizeof(BITMAP), &m_tBit);
	}


	return true;
}

void CTexture::SetPivot(INFO _pivot)
{
	m_tPivot = _pivot;
}

HBITMAP CTexture::GetBitmap()
{
	return m_hBitmap;
}

HDC CTexture::GetDC()
{
	return m_hMemDC;
}
