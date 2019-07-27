#pragma once
#include "GameObject.h"
class CMonBullet :
	public CGameObject
{
public:
	CMonBullet();
	~CMonBullet();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

public:
	void SetInfo(BULLET_TYPE bType, float fAngle);
	float GetAngle(CGameObject* pDesObj, CGameObject* pSrcObj);

public:
	void IsOutRange();
	void IsMoving();

private:
	int m_iDmg;
	float m_fAngle;
	float m_MovingAngle;
	float m_fPlayerAngle;
	float m_fFuse;
	float m_fCooldown;
	BULLET_TYPE m_BulletType;
	CAnimator* m_pAnimator;


};

