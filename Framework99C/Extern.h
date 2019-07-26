#pragma once

#ifndef __EXTERN_H__

// extern 키워드: 외부에 이러한 전역변수가 존재함을 알려주는 키워드.
extern HWND g_hWnd;
extern HDC	g_hDC;
extern HINSTANCE g_hInst;
extern HBITMAP g_hBitmap;

extern float g_fDeltaTime;
extern float g_fElapsedTime;
extern float g_fTimeScale;
extern float g_fTotalTime;

// 키보드
extern const DWORD KEY_UP;
extern const DWORD KEY_DOWN;
extern const DWORD KEY_LEFT;
extern const DWORD KEY_RIGHT;

extern const DWORD KEY_ACTION;
extern const DWORD KEY_SPECIAL;

#define __EXTERN_H__
#endif
