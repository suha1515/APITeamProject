#pragma once
#include "Monster.h"
class CBoss :
	public CMonster
{
public:
	CBoss();
	virtual ~CBoss();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

protected:
	void IsMoving();
	virtual void IsFire() override;

private:
	POINT m_Barrel3;
	POINT m_Barrel4;

	float m_fAngle2;
	float m_fCoolDown2;

	CAnimator* m_pAnimator;


};

