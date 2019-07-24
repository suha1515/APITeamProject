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

	// 이터레이터 패턴 (반복자 패턴)
	// 다형적인 클래스들을 공통된 컨테이너에 담아 반복자로 일괄처리하는 디자인 패턴.

	//메인게임에서 모든 오브젝를 관리하니 접근가능하게
	//-정보성-
	//OBJLIST	m_ObjLst[OBJECT_END];


	// 매니저
	CCollsionMgr* m_pCollsionMgr;
	CPathMgr* m_pPathMgr;
	CResourceMgr* m_pResourceMgr;
	CKeyboardMgr* m_pKeyboardMgr;
	CSpawnManager m_SpawnMonster;
};

