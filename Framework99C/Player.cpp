#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

CPlayer::CPlayer()
{
	//��� ���ӿ�����Ʈ�� ������ ������Ʈ ���� ����Ʈ�� �����͸� �����Ѵ�.
	m_ObjLst[OBJECT_PLAYER].push_back(this);
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::SetBulletLst(OBJLIST* pBulletLst)
{
	m_pBulletLst = pBulletLst;
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tInfo.fSpeed = 350.f;

	m_pTexture = CResourceMgr::LoadTexture("Player", _T("Stage/Player/Player.bmp"));

}

int CPlayer::Update()
{
	KeyInput();
	CGameObject::UpdateRect();

	return NO_EVENT;
}

void CPlayer::Render(HDC hDC)
{
	m_pTexture->Render(hDC);
	TransparentBlt(hDC, m_tInfo.fX - 40, m_tInfo.fY - 40, 80, 80, m_pTexture->GetDC(), 0, 0, 80, 80, RGB(255, 255, 255));
}

void CPlayer::Release()
{
	// ������ ����Ʈ���� ������Ʈ�� ����
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJECT_PLAYER].begin(), m_ObjLst[OBJECT_PLAYER].end(), this);
	if (iter_find != m_ObjLst[OBJECT_PLAYER].end())
	{
		m_ObjLst[OBJECT_PLAYER].erase(iter_find);
	}
}

CGameObject* CPlayer::CreateBullet()
{
	return CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
}

CGameObject* CPlayer::CreateBullet(BULLET_DIRECTION eDir)
{
	CGameObject* pBullet = CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pBullet)->SetDirection(eDir);

	return pBullet;
}

void CPlayer::KeyInput()
{
	VECTOR2D vector(0, 0);
	// ���Ϳ� �浹�ϸ� �ڷ� �о���� - ������ -
	if (CCollsionMgr::CollisionRect(m_ObjLst[OBJECT_PLAYER], m_ObjLst[OBJECT_MONSTER],&vector))
	{
		m_tInfo.fX += vector.x;
		m_tInfo.fY += vector.y;
	}
	else
	{
		//�÷��̾� ���� ���� �����Ÿ��°� ����.
		if (m_tRect.left > 0)
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				m_tInfo.fX -= m_tInfo.fSpeed  * DELTA_TIME;
		}
		if (m_tRect.right < WINCX)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				m_tInfo.fX += m_tInfo.fSpeed  * DELTA_TIME;
		}
		if (m_tRect.top > 0)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
				m_tInfo.fY -= m_tInfo.fSpeed  * DELTA_TIME;
		}
		if (m_tRect.bottom < WINCY)
		{
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
				m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		}
	}

	static int nMaximumBullet = MAXIMUM_MISSILE;

	

	// BUTTON_A : Ű���带 ���� ��� �ִ� 4���� �̻��ϱ��� �߻�
	if (!m_bArrButton[BUTTON_A] && (GetAsyncKeyState('A') & 0x8000))
	{
		m_pBulletLst->push_back(CreateBullet(BULLET_UP));

		if (!(--nMaximumBullet))
		{
			m_bArrButton[BUTTON_A] = true;
			nMaximumBullet = MAXIMUM_MISSILE;
		}
	}
	if (!GetAsyncKeyState('A'))
		m_bArrButton[BUTTON_A] = false;

	// BUTTON_S : �ʻ�� ��ư �����Է� ����
	if (!m_bArrButton[BUTTON_S] && (GetAsyncKeyState('S') & 0x8000))
	{
		m_pBulletLst->push_back(CreateBullet(BULLET_UP));
		m_bArrButton[BUTTON_S] = true;
	}
	if (!GetAsyncKeyState('S'))
		m_bArrButton[BUTTON_S] = false;
	//if (GetAsyncKeyState('W') & 0x8000)
	//	m_pBulletLst->push_back(CreateBullet(BULLET_UP));
	//if (GetAsyncKeyState('D') & 0x8000)
	//	m_pBulletLst->push_back(CreateBullet(BULLET_RIGHT));
}
