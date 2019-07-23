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
	void RunClip(int iIdx); // 애니메이션 실행

private:
	vector<CTexture*> m_vecTexture;
};

