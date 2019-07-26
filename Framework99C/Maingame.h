#pragma once
// a
class CGameObject;
class CMaingame
{
public:
	CMaingame();
	~CMaingame();

public:
	void Initialize();
	void Update();
	void Render();

private:
	void Release();

private:
	HDC		m_hDC;	
	HINSTANCE m_hInst;

	// 더블 버퍼링을 위한 변수
	HDC		m_hMemDC;
	HBITMAP bitmap;
	HBITMAP oldbitmap;


	// 매니저
	CCollsionMgr* m_pCollsionMgr;
	CPathMgr* m_pPathMgr;
	CResourceMgr* m_pResourceMgr;
	CKeyboardMgr* m_pKeyboardMgr;
	CEffectMgr* m_pEffectMgr;
	CSpawnManager m_SpawnMonster;
};

