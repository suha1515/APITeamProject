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

	void SetMonType(int iType);
	void SetDistance();
	void SetBarrel(POINT* pBarrel, float fX, float fY);


protected:
	void IsMoving();
	void IsOutRange();
	virtual void IsFire();

protected:
	int m_iMonType;
	int m_iHP;
	int m_iScore;
	int m_iShotCount;
	float m_fAngle;
	float m_fCoolDown;
	float m_fDistance;

	POINT m_Barrel;
	POINT m_Barrel2;

	CGameObject* m_pTarget;

	OBJLIST* m_pBulletLst;
};

