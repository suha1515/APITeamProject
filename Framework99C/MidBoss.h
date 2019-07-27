#pragma once
#include "Monster.h"
class CMidBoss :
	public CMonster
{
public:
	CMidBoss();
	virtual ~CMidBoss();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	void IsMoving();
	void DeadEffect();
	virtual void IsFire() override;
	void IsDead();


private:
	POINT m_Barrel3;
	POINT m_Barrel4;

	float m_fAngle2;
	float m_fCoolDown2;

	CAnimator* m_pAnimator;

	bool m_DeadEffect;
	float m_DeadTime;


	list<PARTICLE_INFO> m_EffectINFO;
};

