#pragma once
class CCollsionMgr
{
DECLARE_SINGLE_TONE(CCollsionMgr)

private:
	void Initialize();

public:
	// 단순충돌용 AABB
	bool CollisionRect(const OBJLIST& dstLst, const OBJLIST& srcLst);
	CGameObject* CollisionRectReturn(const CGameObject* pDst, OBJECT_TYPE type);
	// 충돌범위를 VECTOR로 반환하는 AABB 버전 3번째 인자에 주소로 넘기면된다.
	void CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst);

	bool CollisionRectEX(const OBJLIST& dstLst, const OBJLIST& srcLst);

private:
	bool CheckSphere(const CGameObject* pDest, const CGameObject* pSource);
};
