#pragma once

#ifndef __DEFINE_H__

#pragma comment (lib, "msimg32")

#define WINCX 700
#define WINCY 1000
#define STAGE_SPEED 100.f	// 일단 절반으로 줄임

#define PI 3.14f

#define DELTA_TIME ((g_fDeltaTime) * (g_fTimeScale))
#define TIME	(g_fTotalTime)

#define ROOT_PATH "ROOT_PATH"
#define TEXTURE_PATH "TEXTURE_PATH"

#define NO_EVENT 0
#define DEAD_OBJ 1

#define MAXIMUM_MISSILE 7

// 싱글톤 매크로
#define DECLARE_SINGLE_TONE(T) \
private:\
	T();\
	~T();\
	static T* m_pInstance;\
public:\
	static T* GetInstance();\
	static void DeleteInstance();


#define DEFINE_SINGLE_TONE(T) \
T* T::m_pInstance = nullptr;\
T::T()\
{}\
T::~T()\
{}\
T* T::GetInstance()\
{\
	if (!m_pInstance)\
	{\
		m_pInstance = new T;\
		m_pInstance->Initialize();\
	}\
	return m_pInstance;\
}\
void T::DeleteInstance()\
{\
	if (m_pInstance)\
	{\
		delete m_pInstance;\
		m_pInstance = nullptr;\
	}\
}

#define NULL_CHECK(ptr) \
if(nullptr ==(ptr)) return ;

#define NULL_CHECK_RETURN(ptr, val) \
if(nullptr ==(ptr)) return val;

#define __DEFINE_H__
#endif
