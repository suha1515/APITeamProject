#include "stdafx.h"
#include "Animator.h"


Animator::Animator()
{
}


Animator::~Animator()
{
	vector<CTexture*>::iterator	iter;
	vector<CTexture*>::iterator	iter_end = m_vecTexture.end();

	for (iter = m_vecTexture.begin(); iter != iter_end; ++iter)
	{
		(*iter)->SafeDelete();
		*iter = nullptr;
	}
	m_vecTexture.clear();

}

void Animator::AddTexture(CTexture* pTexture)
{
	if (pTexture)
	{
		pTexture->AddRef();
		m_vecTexture.push_back(pTexture);
	}
}
