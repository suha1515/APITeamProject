#pragma once

class CTexture;

class Animator
{
public:
	Animator();
	~Animator();

public:
	void AddTexture(CTexture* pTexture);

public:
	void RunClip(int iIdx); // �ִϸ��̼� ����

private:
	vector<CTexture*> m_vecTexture;
};

