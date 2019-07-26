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

	// ���� ���۸��� ���� ����
	HDC		m_hMemDC;
	HBITMAP bitmap;
	HBITMAP oldbitmap;


	// �Ŵ���
	CCollsionMgr* m_pCollsionMgr;
	CPathMgr* m_pPathMgr;
	CResourceMgr* m_pResourceMgr;
	CKeyboardMgr* m_pKeyboardMgr;
	CEffectMgr* m_pEffectMgr;
	CSpawnManager m_SpawnMonster;
};

