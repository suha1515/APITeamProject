#pragma once
//게임 내의 오브젝트를 관리하는 중재자

// 중재자 패턴 (메디에이터 패턴)
// M : N  였던 상호 복잡성을 M : 1 로 낮추는 디자인 패턴
// 모든 오브젝트들은 서로를 몰라도 중재자만 알면 상호 작용 처리 가능

class CGameObject;
class CObjectMgr
{
	DECLARE_SINGLE_TONE(CObjectMgr)
public:
	CGameObject* GetPlayer() const;
	const OBJLIST& GetObjectList(OBJECT_TYPE eType);

public:
	void AddObject(OBJECT_TYPE eType, CGameObject* pObject);
	void Update();
	void Render(HDC hDC);

private:
	void Release();
	void Initialize();
private:
	OBJLIST m_ObjLst[OBJECT_END];
};

