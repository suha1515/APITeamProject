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

	// ���ͷ����� ���� (�ݺ��� ����)
	// �������� Ŭ�������� ����� �����̳ʿ� ��� �ݺ��ڷ� �ϰ�ó���ϴ� ������ ����.

	//���ΰ��ӿ��� ��� �������� �����ϴ� ���ٰ����ϰ�
	//-������-
	//OBJLIST	m_ObjLst[OBJECT_END];


	// �Ŵ���
	CCollsionMgr* m_pCollsionMgr;
	CPathMgr* m_pPathMgr;
	CResourceMgr* m_pResourceMgr;
	CKeyboardMgr* m_pKeyboardMgr;
	CSpawnManager m_SpawnMonster;
};

