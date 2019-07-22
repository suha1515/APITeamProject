#pragma once

#ifndef __STRUCT_H__

typedef struct tagInfo
{
	float fX = 0.f;
	float fY = 0.f;
	float fCX = 0.f;
	float fCY = 0.f;
	float fSpeed = 0.f;

}INFO;

//2������ ���͸� ǥ���ϱ����� ����ü
//-������-
typedef struct tVector2D
{
	tVector2D() {};
	tVector2D(int _x, int _y) :x(_x), y(_y) {};
	int x;
	int y;
}VECTOR2D;

//���� ������ ���� ����ü
//-������-
typedef struct tSpawn_INFO
{
	CMonster* enemy;
	int spwanTime;
};

#define __STRUCT_H__
#endif
