#include "stdafx.h"
#include "ResourceMgr.h"
#include "Texture.h"


DEFINE_SINGLE_TONE(CResourceMgr)

void CResourceMgr::Initialize()
{
	m_hInst = g_hInst;
	m_hDC = g_hDC;
}

CTexture * CResourceMgr::LoadTexture(const string & strKey, const TCHAR * pFileName,
	const string & strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture)
	{
		pTexture->AddRef();
		return pTexture;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName, strPathKey))
	{
		if (pTexture)
		{
			pTexture->SafeDelete();
			pTexture = nullptr;
			return pTexture;
		}
	}
	pTexture->AddRef();
	m_mapTexture.insert(unordered_map<string, CTexture*>::value_type(strKey, pTexture));

	return pTexture;
}

CTexture * CResourceMgr::FindTexture(const string & strKey)
{
	unordered_map<string, CTexture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

HINSTANCE CResourceMgr::GetInst()
{
	return m_hInst;
}
