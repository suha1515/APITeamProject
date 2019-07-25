#pragma once

#include "Texture.h"

class CResourceMgr
{
	DECLARE_SINGLE_TONE(CResourceMgr)

private:
	void Initialize();

public:
	CTexture* LoadTexture(const string& strKey,
		const TCHAR* pFileName, const string& strPathKey = TEXTURE_PATH);
	CTexture* FindTexture(const string& strKey);
	HINSTANCE GetInst();

private:
	unordered_map<string, CTexture*> m_mapTexture;
	HINSTANCE	m_hInst;
	HDC			m_hDC;
};

