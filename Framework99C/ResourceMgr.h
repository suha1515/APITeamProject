#pragma once

#include "Texture.h"

class CResourceMgr
{
public:
	CResourceMgr();
	~CResourceMgr();

public:
	static void Initialize(HINSTANCE hInst, HDC hDC);
	static CTexture* LoadTexture(const string& strKey,
		const TCHAR* pFileName, const string& strPathKey = TEXTURE_PATH);
	static CTexture* FindTexture(const string& strKey);
	static HINSTANCE GetInst();

private:
	static unordered_map<string, CTexture*> m_mapTexture;
	static HINSTANCE	m_hInst;
	static HDC			m_hDC;
};

