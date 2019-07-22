#pragma once

class CPathMgr
{
public:
	CPathMgr();
	~CPathMgr();

public:
	static void Initialize();
	static bool CreatePath(const string& strKey, const TCHAR* pPath,
		const string& strBaseKey = ROOT_PATH);
	static const TCHAR* FindPath(const string& strKey);

private:
	static unordered_map<string, wstring> m_mapPath;
};

