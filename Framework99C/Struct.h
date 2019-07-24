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
	// �߽� ��ǥ
	float fX = 0.f;
	float fY = 0.f;
	// �̹��� �Ǻ�
	float fPivotX = 0.f;
	float fPivotY = 0.f;
	// �̹��� ũ��
	float fImgCX = 0.f;
	float fImgCY = 0.f;

}IMGINFO;

class CTexture;
typedef struct tagAnimInfo
{
	CTexture* pTexture = nullptr;
	ANIMATION_TYPE tAnimType = AT_DEFAULT;

	// ���� ��ġ
	float fMinX = 0.f;
	float fMinY = 0.f;

	// �� ����
	float fMaxX = 1.f;
	float fMaxY = 1.f;

	// ���� ��ġ
	float fCurX = 0.f;
	float fCurY = 0.f;

	float fStartX = 0.f;
	float fStartY = 0.f;

	float fEndX = 0.f;
	float fEndY = 0.f;

	// �ִϸ��̼� ����ð�
	float fElapsedTime = 0.f;
	float fLimitTime = 0.f;

} ANIMINFO;


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
	MONSTER_TYPE type;
	
	int spawnPos_x;
	int spawnPos_y;
	int spawnTime;
}SPAWN_INFO;

#define __STRUCT_H__
#endif
