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
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

protected:
	void IsMoving();
	virtual void IsFire() override;


};

