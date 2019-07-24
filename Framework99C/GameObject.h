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

	CTexture* m_pTexture;

};

