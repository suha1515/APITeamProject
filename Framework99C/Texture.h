#pragma once
class CTexture
{
	friend class ResourceMgr;
public:
	CTexture();
	~CTexture();

public:
	bool LoadTexture(HINSTANCE hInst, HDC hDC, const string& strKey,
		const TCHAR* pFileName, const string& strPathKey = TEXTURE_PATH);

public:
	HDC GetDC();
	BITMAP GetBitmap();
	bool GetKeyEnable();
	COLORREF GetColorKey();
	void Render(HDC hDC);
	

public:
	void SetPivot(INFO pivot);
	void SetColorKey(COLORREF colorKey);
	

private:
	HDC m_hMemDC;

	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	BITMAP m_tBit;

	INFO m_tPivot;

	bool m_bColorKeyEnable;
	COLORREF m_tColorKey;
};

