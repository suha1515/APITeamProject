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
	void AddWingMan();
	void UpdateWingMan();
	POINT* GetWingManPos();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	//�Ѿ� �߻�
	CGameObject* CreateBullet();
	CGameObject* CreateBullet(BULLET_DIRECTION eDir);
	void KeyInput();

private:	
	//OBJLIST*	m_pBulletLst;
	//�÷��̾� ���� ������Ʈ(����) ��ġ
	POINT		m_WingManLoc[4];
	CGameObject*    m_WingMan[4];

	int wingCount;	
	bool m_bArrButton[BUTTON_END];
	bool m_bIsAttack = false;
};

