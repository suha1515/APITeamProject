#pragma once
#include "GameObject.h"
class CWingMan :
	public CGameObject
{
public:
	CWingMan();
	virtual ~CWingMan();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
public:
	void Fire();
	void ChargeShot();
	void Move();
	void SetLocation(POINT* pt);

protected:
	virtual void Release() override;

private:
	CGameObject* CreateBullet();
	POINT*		 m_Location;

	float		 m_FireRate;

	CAnimator* m_pAnimator;
};

