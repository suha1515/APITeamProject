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
	pGameObject = CAbstractFactory<CStage>::CreateObject();
	CObjectMgr::GetInstance()->AddObject(OBJECT_STAGE, pGameObject);
	//m_ObjLst[OBJECT_STAGE].push_back(pGameObject);

	// Player
	pGameObject = CAbstractFactory<CPlayer>::CreateObject();
	CObjectMgr::GetInstance()->AddObject(OBJECT_PLAYER, pGameObject);
	//윙맨 추가 -테스트-
	//dynamic_cast<CPlayer*>(pGameObject)->AddWingMan();
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
	monsterPool[0].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[0].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[0].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[0].monster_various = 0;



	monsterPool[1].spawnPos_x = 250;
	monsterPool[1].spawnPos_y = -100;
	monsterPool[1].spawnTime = 6400;
	monsterPool[1].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[1].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[1].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[1].monster_various = 1;


	monsterPool[2].spawnPos_x = 350;
	monsterPool[2].spawnPos_y = -100;
	monsterPool[2].spawnTime = 6300;
	monsterPool[2].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[2].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[2].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[2].monster_various = 0;

	monsterPool[3].spawnPos_x = 450;
	monsterPool[3].spawnPos_y = -100;
	monsterPool[3].spawnTime = 6200;
	monsterPool[3].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[3].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[3].move_type = MONSTER_MOVETYPE::TO_PLAYERX;
	monsterPool[3].monster_various = 3;

	m_SpawnMonster.SetEnemyPool(monsterPool[0]);
	m_SpawnMonster.SetEnemyPool(monsterPool[1]);
	m_SpawnMonster.SetEnemyPool(monsterPool[2]);
	m_SpawnMonster.SetEnemyPool(monsterPool[3]);
}

void CMaingame::Update()
{
	m_SpawnMonster.SpawnEnemy();
	CKeyboardMgr::GetInstance()->Update();
	CObjectMgr::GetInstance()->Update();
}

void CMaingame::Render()
{
	CObjectMgr::GetInstance()->Render(m_hMemDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
}	

void CMaingame::Release()
{
	// GetDC함수로 할당받은 DC는 아래 함수로 해제해주어야 한다.
	bitmap = (HBITMAP)SelectObject(m_hMemDC, oldbitmap);
	DeleteObject(bitmap);
	DeleteDC(m_hMemDC);

	// 매니저 해제
	CCollsionMgr::DeleteInstance();
	CPathMgr::DeleteInstance();
	CResourceMgr::DeleteInstance();
	CKeyboardMgr::DeleteInstance();
}
