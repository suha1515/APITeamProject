#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	const INFO& GetInfo() const;
	const RECT& GetRect() const;
	const bool GetDead() const;

public:
	void SetPos(float x, float y);
	void SetDead(bool bIsDead);

	// virtual
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC hDC) = 0;

public :
	// 모든 게임오브젝트는 이 멤버변수에 들어간다.
	// -정보성-
	static OBJLIST	m_ObjLst[OBJECT_END];

protected:
	virtual void Release() = 0;

protected:
	void UpdateRect();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	
	bool	m_bIsDead;

	CTexture* m_pTexture;

};

