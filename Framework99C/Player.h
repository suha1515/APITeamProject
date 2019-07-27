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
	void UpdateBarrel();
	POINT* GetWingManPos();

	void UpdateCollider();

public:
	void LevelUp();

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
	//����� ����
	void SpecialAttack();
	//������ ���� �Ѿ� ��Ų �ٸ���
	CGameObject* CreateBullet(BULLET_DIRECTION eDir,POINT pos, PLAYER_BULLET_TYPE type);
	void KeyInput();
	void Respawn();

private:	
	//OBJLIST*	m_pBulletLst;
	//�÷��̾� ���� ������Ʈ(����) ��ġ
	POINT		m_WingManLoc[4];
	//�÷��̾� �ѱ� ��ġ
	POINT		m_Barrel[5];
	CGameObject*    m_WingMan[4];

	//�÷��̾� �Ŀ� ����
	int m_PowerLevel;
	//�÷��̾� �ʻ�� ����
	int m_BombCount;
	//�÷��̾� ��� ����
	int m_PlayerLife;


	int wingCount;
	float fFireRate;
	float fWingFireRate;
	float chargeTime;
	float chargeShotTime;

	float bombCoolTime;
	float invincibleTime;

	bool m_bArrButton[BUTTON_END];


	//--------Test-----------
	//CAnimator* m_pAnimator;

	bool m_bIsAttack = false;
	bool m_chargeShot = false;
	bool m_chargeWIngman = false;
	bool m_IsSpecialAttack;
	bool m_IsDead = false;

	// TEST ---------------------------------------------------
	CAnimator* m_pAnimator;
	// --------------------------------------------------------
	CTexture* m_SpecialAttack;

	IMGINFO m_BigPlane;

	list<pair<POINT, float>> bombDrop;
};

