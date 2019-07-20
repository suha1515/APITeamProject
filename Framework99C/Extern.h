#pragma once

#ifndef __EXTERN_H__

// extern 키워드: 외부에 이러한 전역변수가 존재함을 알려주는 키워드.
extern HWND g_hWnd;
extern HDC	g_hDC;
extern HBITMAP g_hBitmap;

extern float g_fDeltaTime;
extern float g_fElapsedTime;
extern float g_fTimeScale;

#define __EXTERN_H__
#endif
