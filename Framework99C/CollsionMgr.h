#pragma once
class CCollsionMgr
{
public:
	CCollsionMgr();
	~CCollsionMgr();

public:
	static void CollisionRect(const OBJLIST& dstLst, const OBJLIST& srcLst);
	static void CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst);

private:
	static bool CheckSphere(const CGameObject* pDest, const CGameObject* pSource);
};

