#pragma once
#include "GameObject.h"

class CTexture;
class CStage :
	public CGameObject
{
public:
	CStage();
	virtual ~CStage();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CTexture* m_pTexture;
};

