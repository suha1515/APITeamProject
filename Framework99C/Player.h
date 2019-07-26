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
	void AddWingMan();
	void UpdateWingMan();
	void UpdateBarrel();
	POINT* GetWingManPos();

	void UpdateCollider();

public:
	void LevelUp();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	//총알 발사
	CGameObject* CreateBullet();
	//레벨에 따른 총알 스킨 다르게
	CGameObject* CreateBullet(BULLET_DIRECTION eDir,POINT pos, PLAYER_BULLET_TYPE type);
	void KeyInput();

private:	
	//OBJLIST*	m_pBulletLst;
	//플레이어 보조 오브젝트(윙맨) 위치
	POINT		m_WingManLoc[4];
	//플레이어 총구 위치
	POINT		m_Barrel[5];
	CGameObject*    m_WingMan[4];

	//플레이어 파워 레벨
	int m_PowerLevel;
	//플레이어 필살기 개수
	int m_BombCount;
	//플레이어 목숨 개수
	int m_PlayerLife;

	int wingCount;
	float fFireRate;
	float fWingFireRate;
	float chargeTime;
	float chargeShotTime;
	bool m_bArrButton[BUTTON_END];


	//--------Test-----------
	//CAnimator* m_pAnimator;

	bool m_bIsAttack = false;
	bool m_chargeShot = false;
	bool m_chargeWIngman = false;


	// TEST ---------------------------------------------------
	CAnimator* m_pAnimator;
	// --------------------------------------------------------

};

