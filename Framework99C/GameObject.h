#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	const INFO& GetInfo() const;
	const RECT& GetRect() const;

public:
	void SetPos(float x, float y);
	void SetDead(bool bIsDead);

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC hDC) = 0;

protected:
	virtual void Release() = 0;

protected:
	void UpdateRect();
	void UpdateImgInfo(float CImgX, float CImgY);

protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	IMGINFO	m_tImgInfo;

	
	bool	m_bIsDead;

	// 모든 게임오브젝트는 이 멤버변수에 들어간다.
	// -정보성-
	static OBJLIST	m_ObjLst[OBJECT_END];

	CTexture* m_pTexture;

};

