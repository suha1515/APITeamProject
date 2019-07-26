#pragma once
#include "GameObject.h"
class CBullet :
	public CGameObject
{
public:
	CBullet();
	virtual ~CBullet();

public:
	void SetDirection(BULLET_DIRECTION eDir);
	void SetBulletType(PLAYER_BULLET_TYPE type);

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	void IsMoving();
	void IsOutRange();

private:
	BULLET_DIRECTION	m_eDirection;
	PLAYER_BULLET_TYPE  m_BulletType;

	CAnimator* m_pAnimator;
};

