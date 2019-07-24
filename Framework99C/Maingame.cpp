#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Monster.h"
#include "CommonMonster.h"
#include "Stage.h"

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
	m_hInst = g_hInst;
	m_hMemDC = CreateCompatibleDC(m_hDC);

	bitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	oldbitmap = (HBITMAP)SelectObject(m_hMemDC, bitmap);
	srand((unsigned)time(nullptr));

	// CollisionMgr
	m_pCollsionMgr = CCollsionMgr::GetInstance();

	// PathMgr
	m_pPathMgr = CPathMgr::GetInstance();

	// ResourceMgr
	m_pResourceMgr = CResourceMgr::GetInstance();

	// KeyboardMgr
	m_pKeyboardMgr = CKeyboardMgr::GetInstance();

	CGameObject* pGameObject = nullptr;

	// Stage
	CAbstractFactory<CStage>::CreateObject();
	//m_ObjLst[OBJECT_STAGE].push_back(pGameObject);

	// Player
	pGameObject = CAbstractFactory<CPlayer>::CreateObject();
	//dynamic_cast<CPlayer*>(pGameObject)->SetBulletLst(&m_ObjLst[OBJLECT_BULLET]);
	//m_ObjLst[OBJECT_PLAYER].push_back(pGameObject);

	//// Monster
	//for (int i = 0; i < 1; ++i)
	//{
	//	//float x = float(rand() % (WINCX - 200)) + 100.f;
	//	//float y = float(rand() % (WINCY - 200)) + 100.f;

	//	//pGameObject = CAbstractFactory<CMonster>::CreateObject();
	//	pGameObject = CAbstractFactory<CCommonMonster>::CreateObject();
	//	// 몬스터 생성시, 몬스터의 탄환리스트와 플레이어 리스트를 넘겨준다.
	//	//dynamic_cast<CCommonMonster*>(pGameObject)->SetBulletLst(&m_ObjLst[OBJECT_MONBULLET]);
	//	dynamic_cast<CCommonMonster*>(pGameObject)->SetPlayer(*(CGameObject::m_ObjLst[OBJECT_PLAYER].begin()));

	//	//m_ObjLst[OBJECT_MONSTER].push_back(pGameObject);
	//}
	SPAWN_INFO monsterPool[4];
	monsterPool[0].spawnPos_x = 150;
	monsterPool[0].spawnPos_y = -100;
	monsterPool[0].spawnTime = 6500;
	monsterPool[0].type = MONSTER_TYPE::DEFAULT;

	monsterPool[1].spawnPos_x = 250;
	monsterPool[1].spawnPos_y = -100;
	monsterPool[1].spawnTime = 6400;
	monsterPool[1].type = MONSTER_TYPE::DEFAULT;

	monsterPool[2].spawnPos_x = 350;
	monsterPool[2].spawnPos_y = -100;
	monsterPool[2].spawnTime = 6300;
	monsterPool[2].type = MONSTER_TYPE::DEFAULT;

	monsterPool[3].spawnPos_x = 450;
	monsterPool[3].spawnPos_y = -100;
	monsterPool[3].spawnTime = 6200;
	monsterPool[3].type = MONSTER_TYPE::DEFAULT;

	m_SpawnMonster.SetEnemyPool(monsterPool[0]);
	m_SpawnMonster.SetEnemyPool(monsterPool[1]);
	m_SpawnMonster.SetEnemyPool(monsterPool[2]);
	m_SpawnMonster.SetEnemyPool(monsterPool[3]);
}

void CMaingame::Update()
{
	m_SpawnMonster.SpawnEnemy();
	// 이터레이터 패턴 (반복자 패턴)
	// 다형적인 클래스들을 공통된 컨테이너에 담아 반복자로 일괄처리하는 디자인 패턴.
	for (int i = 0; i < OBJECT_END; ++i)
	{
		OBJLIST::iterator iter_Begin = CGameObject::m_ObjLst[i].begin();
		OBJLIST::iterator iter_End = CGameObject::m_ObjLst[i].end();

		for (; iter_Begin != iter_End;)
		{
			int iEvent = (*iter_Begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete((*iter_Begin));
				iter_Begin = CGameObject::m_ObjLst[i].erase(iter_Begin);
				//++iter_Begin;
			}
			else
				++iter_Begin;
		}
	}	


	m_pCollsionMgr->CollisionRect(CGameObject::m_ObjLst[OBJECT_MONSTER], CGameObject::m_ObjLst[OBJLECT_BULLET]);
  //CCollsionMgr::CollisionSphere(m_ObjLst[OBJECT_MONSTER], m_ObjLst[OBJLECT_BULLET]);
}

void CMaingame::Render()
{
	// 이터레이터 패턴 (반복자 패턴)
	// 다형적인 클래스들을 공통된 컨테이너에 담아 반복자로 일괄처리하는 디자인 패턴.
	for (int i = 0; i < OBJECT_END; ++i)
	{
		OBJLIST::iterator iter_Begin = CGameObject::m_ObjLst[i].begin();
		OBJLIST::iterator iter_End = CGameObject::m_ObjLst[i].end();
		for (; iter_Begin != iter_End;)
		{
			(*iter_Begin)->Render(m_hMemDC);
			++iter_Begin;
		}
			
	}

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
}	

void CMaingame::Release()
{
	// GetDC함수로 할당받은 DC는 아래 함수로 해제해주어야 한다.
	bitmap = (HBITMAP)SelectObject(m_hMemDC, oldbitmap);
	DeleteObject(bitmap);
	DeleteDC(m_hMemDC);

	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(CGameObject::m_ObjLst[i].begin(), CGameObject::m_ObjLst[i].end(), SafeDelete<CGameObject*>);
		CGameObject::m_ObjLst[i].clear();
	}	

	// 매니저 해제
	CCollsionMgr::DeleteInstance();
	CPathMgr::DeleteInstance();
	CResourceMgr::DeleteInstance();
	CKeyboardMgr::DeleteInstance();

}
