#pragma once
class CTexture
{
public:
	CTexture();
	~CTexture();

public:
	void Render(HDC hDC);

public:
	bool SetTexture(HINSTANCE _hInst, wstring _strPath, wstring _strFileName);
	void SetPivot(INFO _pivot);

public:
	HBITMAP GetBitmap();
	HDC	GetDC();

private:
	HDC m_hDC;
	HDC m_hMemDC;

	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	BITMAP m_tBit;

	INFO m_tPivot;
};

