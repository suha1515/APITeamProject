#pragma once
class CCollsionMgr
{
public:
	CCollsionMgr();
	~CCollsionMgr();

public:
	// 단순충돌용 AABB
	static bool CollisionRect(const OBJLIST& dstLst, const OBJLIST& srcLst);
	// 충돌범위를 VECTOR로 반환하는 AABB 버전 3번째 인자에 주소로 넘기면된다.
	static bool CollisionRectEX(const OBJLIST& dstLst, const OBJLIST& srcLst);
	static void CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst);

private:
	static bool CheckSphere(const CGameObject* pDest, const CGameObject* pSource);
};

