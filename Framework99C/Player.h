#pragma once
/*
	�÷��̾� ��ũ��Ʈ by ������

	���� : �÷��̾ ȣ���ϴ� �Լ��� ��� ����
*/

#include "GameObject.h"
class CPlayer :
	public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetBulletLst(OBJLIST* pBulletLst);

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	CGameObject* CreateBullet();
	CGameObject* CreateBullet(BULLET_DIRECTION eDir);
	void KeyInput();

private:	
	OBJLIST*	m_pBulletLst;

	bool m_bArrButton[BUTTON_END];


	//--------Test-----------
	CAnimator* m_pAnimator;
};

