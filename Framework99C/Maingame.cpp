#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Monster.h"
#include "CommonMonster.h"
#include "Stage.h"
#include "Items.h"


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

	// Item Test
	pGameObject = CAbstractFactory<CItems>::CreateObject();
	pGameObject->SetPos(100, 100);
	dynamic_cast<CItems*>(pGameObject)->SetType(ITEM_TYPE::SPECIAL);
	dynamic_cast<CItems*>(pGameObject)->Initialize();
	CObjectMgr::GetInstance()->AddObject(OBJECT_ITEM, pGameObject);


	m_SpawnMonster.Initialize();
	CEffectMgr::GetInstance()->AddEffect(E_MINIPLANE_DESTROIED);
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
	IMGINFO testInfo(500, 400, 0.5, 0.5, 200, 200, 1, 1 );
	CEffectMgr::GetInstance()->AnimateEffect(m_hMemDC, testInfo);
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
}
