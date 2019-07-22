#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Monster.h"
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
	// GetDC: ��� DC ���� �Լ�.
	m_hDC = g_hDC;
	m_hInst = g_hInst;
	m_hMemDC = CreateCompatibleDC(m_hDC);

	bitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	oldbitmap = (HBITMAP)SelectObject(m_hMemDC, bitmap);
	srand((unsigned)time(nullptr));

	CPathMgr::Initialize();

	CResourceMgr::Initialize(m_hInst, m_hDC);

	CGameObject* pGameObject = nullptr;

	// Stage
	pGameObject = CAbstractFactory<CStage>::CreateObject();
	m_ObjLst[OBJECT_STAGE].push_back(pGameObject);

	// Player
	pGameObject = CAbstractFactory<CPlayer>::CreateObject();
	dynamic_cast<CPlayer*>(pGameObject)->SetBulletLst(&m_ObjLst[OBJLECT_BULLET]);
	m_ObjLst[OBJECT_PLAYER].push_back(pGameObject);

	// Monster
	for (int i = 0; i < 1; ++i)
	{
		//float x = float(rand() % (WINCX - 200)) + 100.f;
		//float y = float(rand() % (WINCY - 200)) + 100.f;

		pGameObject = CAbstractFactory<CMonster>::CreateObject();
		m_ObjLst[OBJECT_MONSTER].push_back(pGameObject);
	}
}

void CMaingame::Update()
{
	// ���ͷ����� ���� (�ݺ��� ����)
	// �������� Ŭ�������� ����� �����̳ʿ� ��� �ݺ��ڷ� �ϰ�ó���ϴ� ������ ����.
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

	CCollsionMgr::CollisionRect(m_ObjLst[OBJECT_MONSTER], m_ObjLst[OBJLECT_BULLET]);
	//CCollsionMgr::CollisionSphere(m_ObjLst[OBJECT_MONSTER], m_ObjLst[OBJLECT_BULLET]);
}

void CMaingame::Render()
{
	CMonster monster;
	monster.Update();
	monster.Render(m_hDC);

	// ���ͷ����� ���� (�ݺ��� ����)
	// �������� Ŭ�������� ����� �����̳ʿ� ��� �ݺ��ڷ� �ϰ�ó���ϴ� ������ ����.
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto& pObject : m_ObjLst[i])
			pObject->Render(m_hMemDC);
	}

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
}	

void CMaingame::Release()
{
	// GetDC�Լ��� �Ҵ���� DC�� �Ʒ� �Լ��� �������־�� �Ѵ�.
	bitmap = (HBITMAP)SelectObject(m_hMemDC, oldbitmap);
	DeleteObject(bitmap);
	DeleteDC(m_hMemDC);

	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<CGameObject*>);
		m_ObjLst[i].clear();
	}	
}
