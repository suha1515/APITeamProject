#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Monster.h"
#include "CommonMonster.h"
#include "Stage.h"
#include "Items.h"


#include "Boss.h"

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

	// EffectMgr
	m_pEffectMgr = CEffectMgr::GetInstance();

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
	//	float x = float(rand() % (WINCX - 200)) + 100.f;
	//	float y = float(rand() % (WINCY - 200)) + 100.f;

	//	pGameObject = CAbstractFactory<CMonster>::CreateObject();
	//	pGameObject = CAbstractFactory<CCommonMonster>::CreateObject();
	//	// 몬스터 생성시, 몬스터의 탄환리스트와 플레이어 리스트를 넘겨준다.
	//	dynamic_cast<CCommonMonster*>(pGameObject)->SetBulletLst(&m_ObjLst[OBJECT_MONBULLET]);
	//	dynamic_cast<CCommonMonster*>(pGameObject)->SetPlayer(*(CGameObject::m_ObjLst[OBJECT_PLAYER].begin()));

	//	m_ObjLst[OBJECT_MONSTER].push_back(pGameObject);
	//}

	// 보스 테스트용
	CGameObject *object = CAbstractFactory<CBoss>::CreateObject();
	object->SetPos(375, -300);
	dynamic_cast<CBoss*>(object)->SetMonType(BOSS, SINGLE, RIGHT, 0);
	dynamic_cast<CBoss*>(object)->Initialize();
	CObjectMgr::GetInstance()->AddObject(OBJECT_MONSTER, object);

	// Item Test
	pGameObject = CAbstractFactory<CItems>::CreateObject();
	pGameObject->SetPos(100, 100);
	dynamic_cast<CItems*>(pGameObject)->SetType(ITEM_TYPE::SPECIAL);
	dynamic_cast<CItems*>(pGameObject)->Initialize();
	CObjectMgr::GetInstance()->AddObject(OBJECT_ITEM, pGameObject);


	m_SpawnMonster.Initialize();

}

void CMaingame::Update()
{
	//m_SpawnMonster.SpawnEnemy();
	CKeyboardMgr::GetInstance()->Update();
	CObjectMgr::GetInstance()->Update();
}

void CMaingame::Render()
{
	CObjectMgr::GetInstance()->Render(m_hMemDC);

	CEffectMgr::GetInstance()->AnimateEffect(m_hMemDC);

	CUserInterfaceMgr::GetInstance()->ShowUI(m_hMemDC);

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
	CEffectMgr::GetInstance()->DeleteAnimator();
	CEffectMgr::DeleteInstance();
	CUserInterfaceMgr::DeleteInstance();
}
