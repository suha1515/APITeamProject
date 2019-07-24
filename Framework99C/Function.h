#pragma once

#ifndef __FUNCTION_H__

template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}
//거리 구하는 함수
inline float Distance(const int& px1, const int& py1,const int& px2,const int& py2)
{
	float dx = abs(px1 - px2);
	float dy = abs(py1 - py2);
	float dist = sqrt(dx*dx + dy*dy);
	return dist;
}
//각도 구하는 함수
inline float GetAngle(const float& base, const float& height)
{
	return atan2f(height, base);
}

#define __FUNCTION_H__
#endif
