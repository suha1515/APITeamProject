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
	void SetAngle(float fAngle);

public:
	void IsOutRange();
	void IsMoving();

private:
	int m_iDmg;
	float m_fAngle;
};

