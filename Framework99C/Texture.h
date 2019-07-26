#pragma once

class CTexture
{
	friend class CAnimator;
	friend class ResourceMgr;

public:
	CTexture();
	~CTexture();

public:
	bool LoadTexture(HINSTANCE hInst, HDC hDC, const string& strKey,
		const TCHAR* pFileName, const string& strPathKey = TEXTURE_PATH);
	void AddRef();
	void SafeDelete();

public:
	HDC GetDC();
	BITMAP GetBitmap();
	bool GetKeyEnable();
	COLORREF GetColorKey();
	void DrawTexture(HDC hDC, IMGINFO& imgInfo, float startX = 0, float startY = 0, float maxX = 1, float maxY = 1, float scaleX = 1.f, float scaleY = 1.f);
	

public:
	void SetColorKey(COLORREF colorKey);
	void SetKeyEnable(bool keyEnable);

private:
	int nTextureRef;
	HDC m_hMemDC;

	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	BITMAP m_tBit;

	bool m_bColorKeyEnable;
	COLORREF m_tColorKey;

};

