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

private:
	virtual void Release() override;

private:
	void IsMoving();
	virtual void IsFire() override;

private:
	POINT m_Barrel3;
	POINT m_Barrel4;

	float m_fAngle2;

};

