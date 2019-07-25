#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

public:
	// ��ü ���� ������ �������� ������ �����ϰų�, �÷��̾�-������ �ѱ� ���� ������ ������.
	float GetAngle(CGameObject* pDesObj, CGameObject* pSrcObj);
	float GetAngle(CGameObject* pDesObj, POINT* pPoint);

public:
	void SetDamaged(int dmg);
	void SetBulletLst(OBJLIST* pBulletLst);
	void SetPlayer(CGameObject* pPlayer);

public:
	void SetMonType(int iType);

protected:
	void IsMoving();
	void IsOutRange();
	virtual void IsFire();

protected:
	int m_iMonType;
	int m_iHP;
	int m_iScore;
	float m_fAngle;
	float m_fCoolDown;

	POINT m_Barrel;

	OBJLIST* m_pBulletLst;
	CGameObject* m_pPlayer;
};

