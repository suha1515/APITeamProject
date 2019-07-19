#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Monster.h"

CMaingame::CMaingame()	
{
}

CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Initialize()
{
	// GetDC: 출력 DC 생성 함수.
	m_hDC = g_hDC;

	srand((unsigned)time(nullptr));

	CGameObject* pGameObject = nullptr;

	// Player
	pGameObject = CAbstractFactory<CPlayer>::CreateObject();
	dynamic_cast<CPlayer*>(pGameObject)->SetBulletLst(&m_ObjLst[OBJLECT_BULLET]);
	m_ObjLst[OBJECT_PLAYER].push_back(pGameObject);

	// Monster
	for (int i = 0; i < 5; ++i)
	{
		float x = float(rand() % (WINCX - 200)) + 100.f;
		float y = float(rand() % (WINCY - 200)) + 100.f;

		pGameObject = CAbstractFactory<CMonster>::CreateObject(x, y);
		m_ObjLst[OBJECT_MONSTER].push_back(pGameObject);
	}
}

void CMaingame::Update()
{
	// 이터레이터 패턴 (반복자 패턴)
	// 다형적인 클래스들을 공통된 컨테이너에 담아 반복자로 일괄처리하는 디자인 패턴.
	for (int i = 0; i < OBJECT_END; ++i)
	{
		OBJLIST::iterator iter_Begin = m_ObjLst[i].begin();
		OBJLIST::iterator iter_End = m_ObjLst[i].end();

		for (; iter_Begin != iter_End; )
		{
			int iEvent = (*iter_Begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_Begin);
				iter_Begin = m_ObjLst[i].erase(iter_Begin);
			}
			else
				++iter_Begin;
		}
	}	

	//CCollsionMgr::CollisionRect(m_ObjLst[OBJECT_MONSTER], m_ObjLst[OBJLECT_BULLET]);
	CCollsionMgr::CollisionSphere(m_ObjLst[OBJECT_MONSTER], m_ObjLst[OBJLECT_BULLET]);
}

void CMaingame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	// 이터레이터 패턴 (반복자 패턴)
	// 다형적인 클래스들을 공통된 컨테이너에 담아 반복자로 일괄처리하는 디자인 패턴.
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto& pObject : m_ObjLst[i])
			pObject->Render(m_hDC);
	}

	BitBlt(GetDC(g_hWnd), 0, 0, WINCX, WINCY, g_hDC, 0, 0, SRCCOPY);
}	

void CMaingame::Release()
{
	// GetDC함수로 할당받은 DC는 아래 함수로 해제해주어야 한다.
	ReleaseDC(g_hWnd, m_hDC);

	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<CGameObject*>);
		m_ObjLst[i].clear();
	}	
}
