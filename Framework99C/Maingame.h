#pragma once
// a
class CGameObject;
class CMaingame
{
public:
	CMaingame();
	~CMaingame();

public:
	void Initialize();
	void Update();
	void Render();

private:
	void Release();

private:
	HDC		m_hDC;	

	// ���ͷ����� ���� (�ݺ��� ����)
	// �������� Ŭ�������� ����� �����̳ʿ� ��� �ݺ��ڷ� �ϰ�ó���ϴ� ������ ����.

	//���ΰ��ӿ��� ��� �������� �����ϴ� ���ٰ����ϰ�
	//-������-
	OBJLIST	m_ObjLst[OBJECT_END];
};

