#include "stdafx.h"
#include "PathMgr.h"

DEFINE_SINGLE_TONE(CPathMgr)

void CPathMgr::Initialize()
{
	TCHAR strPath[MAX_PATH] = {};

	// GetCurrentDirectory 
	// ������ : �������� ������ ���� �������Ϸ� ������ ���� ���丮 ��ΰ� �ٸ���
	// ������ : ���� �̸��� �ٲٸ� �ν��� �� ��

	GetModuleFileName(NULL, strPath, MAX_PATH);

	for (int i = lstrlen(strPath) - 1; i >= 0; --i)
	{
		if (strPath[i] == '/' || strPath[i] == '\\')
		{
			memset(strPath + (i + 1), 0, sizeof(TCHAR) * (MAX_PATH - (i + 1)));
			break;
		}
	}

	m_mapPath.insert(unordered_map<string, wstring>::value_type(ROOT_PATH, strPath));


	// Texture ��� ����
	if(!CreatePath(TEXTURE_PATH, _T("Texture/")))
		return;
}

bool CPathMgr::CreatePath(const string & strKey, const TCHAR * pPath, const string & strBaseKey)
{
	const TCHAR* pBasePath = FindPath(strBaseKey);

	wstring strPath;

	if (pBasePath)
		strPath = pBasePath;

	strPath += pPath;

	m_mapPath.insert(unordered_map<string, wstring>::value_type(strKey, strPath));
	return true;
}

const TCHAR * CPathMgr::FindPath(const string & strKey)
{
	unordered_map<string, wstring>::iterator	iter = m_mapPath.find(strKey);


	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second.c_str();
}
