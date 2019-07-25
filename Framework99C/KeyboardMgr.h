#pragma once

class CKeyboardMgr
{
DECLARE_SINGLE_TONE(CKeyboardMgr)

private:
	DWORD m_dwKey;
	DWORD m_dwKeyDown;
	DWORD m_dwKeyUp;

private:
	void Initialize();

public:
	void Update();
	bool KeyPressed(DWORD dwCurKey);
	bool KeyDown(DWORD dwCurKey);
	bool KeyUp(DWORD dwCurKey);

	
};

