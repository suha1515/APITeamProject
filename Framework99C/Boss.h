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
	void PhaseShift();

private:
	POINT m_Barrel3;
	POINT m_Barrel4;

	int m_iShotCount2;
	int m_iShotCount3;

	float m_fAngle2;
	float m_fCoolDown2;
	float m_fCoolDown3;
	float m_fCoolDown4;

	float m_transTime;

	int m_TransPhase;


	CAnimator* m_pAnimator;
	CAnimator* m_pAnimatorHead;
	CAnimator* m_pAnimatorLeg1;
	CAnimator* m_pAnimatorLeg2;
	CAnimator* m_pAnimatorLeg3;
	CAnimator* m_pAnimatorLeg4;

	IMGINFO m_BossHeadInfo;
	IMGINFO m_BossLegInfo1;
	IMGINFO m_BossLegInfo2;
	IMGINFO m_BossLegInfo3;
	IMGINFO m_BossLegInfo4;

};

