#pragma once

class CPathMgr
{
	DECLARE_SINGLE_TONE(CPathMgr)

private:
	void Initialize();
public:
	bool CreatePath(const string& strKey, const TCHAR* pPath,
		const string& strBaseKey = ROOT_PATH);
	const TCHAR* FindPath(const string& strKey);

private:
	unordered_map<string, wstring> m_mapPath;
};

