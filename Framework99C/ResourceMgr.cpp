#include "stdafx.h"
#include "ResourceMgr.h"
#include "Texture.h"

unordered_map<string, CTexture*> CResourceMgr::m_mapTexture;
HINSTANCE	CResourceMgr::m_hInst = NULL;
HDC			CResourceMgr::m_hDC = NULL;


CResourceMgr::CResourceMgr()
{
}


CResourceMgr::~CResourceMgr()
{
}

void CResourceMgr::Initialize(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;
}

CTexture * CResourceMgr::LoadTexture(const string & strKey, const TCHAR * pFileName,
	const string & strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName, strPathKey))
	{
		if (pTexture)
		{
			cout << "파일을 불러올 수 없습니다" << endl;
			delete pTexture;
			pTexture = nullptr;
			return pTexture;
		}
	}

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
