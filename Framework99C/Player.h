#pragma once
/*
	플레이어 스크립트 by 정보성

	설명 : 플레이어가 호출하는 함수및 사용 변수
*/

#include "GameObject.h"
class CPlayer :
	public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetBulletLst(OBJLIST* pBulletLst);

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	CGameObject* CreateBullet();
	CGameObject* CreateBullet(BULLET_DIRECTION eDir);
	void KeyInput();

private:	
	OBJLIST*	m_pBulletLst;

	bool m_bArrButton[BUTTON_END];


	//--------Test-----------
	CAnimator* m_pAnimator;
};

