#pragma once
#include "GameObject.h"
class CMonBullet :
	public CGameObject
{
public:
	CMonBullet();
	~CMonBullet();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

public:
	void SetInfo(BULLET_TYPE bType, float fAngle);

public:
	void IsOutRange();
	void IsMoving();

private:
	int m_iDmg;
	float m_fAngle;
	float m_fFuse;
	BULLET_TYPE m_BulletType;
};

