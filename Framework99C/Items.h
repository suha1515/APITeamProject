#pragma once
#include "GameObject.h"
class CItems :
	public CGameObject
{
public:
	CItems();
	~CItems();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render(HDC hDC);

public:
	void Move();
	void IsOutofRange();

protected:
	virtual void Release();

private:
	float	m_TimeLimit;
	float	m_RandomAngle;
	bool    m_IsAvailable;

	ITEM_TYPE m_Type;
	CAnimator* m_pAnimator;


};

