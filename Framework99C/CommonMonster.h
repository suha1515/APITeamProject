#pragma once
#include "Monster.h"
class CCommonMonster :
	public CMonster
{
public:
	CCommonMonster();
	virtual ~CCommonMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;

private:
	virtual void Release() override;

private:
	void IsMoving();
	virtual void IsFire() override;


};

