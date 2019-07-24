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

typedef struct tagImgInfo
{
	// 중심 좌표
	float fX = 0.f;
	float fY = 0.f;
	// 이미지 피봇
	float fPivotX = 0.f;
	float fPivotY = 0.f;
	// 이미지 크기
	float fImgCX = 0.f;
	float fImgCY = 0.f;

}IMGINFO;
//2차원상 벡터를 표현하기위한 구조체
//-정보성-
typedef struct tVector2D
{
	tVector2D() {};
	tVector2D(int _x, int _y) :x(_x), y(_y) {};
	int x;
	int y;
}VECTOR2D;

//몬스터 스폰을 위한 구조체
//-정보성-
typedef struct tSpawn_INFO
{
	MONSTER_TYPE type;
	
	int spawnPos_x;
	int spawnPos_y;
	int spawnTime;
}SPAWN_INFO;

#define __STRUCT_H__
#endif
