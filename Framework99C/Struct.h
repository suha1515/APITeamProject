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
	tagImgInfo()
	{
		fX = 0.f;
		fY = 0.f;

		fPivotX = 0.f;
		fPivotY = 0.f;

		fImgCX = 0.f;
		fImgCY = 0.f;

		fScaleX = 1.f;
		fScaleY = 1.f;
	}

	tagImgInfo(float x, float y, float pivotX, float pivotY, float imgCX, float imgCY, float scaleX = 1.f, float scaleY = 1.f)
	{
		fX = x;
		fY = y;

		fPivotX = pivotX;
		fPivotY = pivotY;

		fImgCX = imgCX;
		fImgCY = imgCY;

		fScaleX = scaleX;
		fScaleY = scaleY;
	}
	// �߽� ��ǥ
	float fX;
	float fY;
	// �̹��� �Ǻ�
	float fPivotX;
	float fPivotY;
	// �̹��� ũ��
	float fImgCX;
	float fImgCY;
	// �̹��� ���̱�
	float fScaleX;
	float fScaleY;
}IMGINFO;

class CTexture;
typedef struct tagAnimInfo
{
	tagAnimInfo()
	{
		pTexture = nullptr;
		eAnimType = AT_LOOP;

		fMaxX = 1.f;
		fMaxY = 1.f;

		fStartX = 0.f;
		fStartY = 0.f;

		fCurX = 0.f;
		fCurY = 0.f;

		fEndX = 0.f;
		fEndY = 0.f;

		fAccumulatedTime = 0.f;
		fElapsedTime = 0.f;
		fLimitTime = 0.f;

		bIsEnd = false;
	}

	tagAnimInfo(CTexture* texture, ANIMATION_TYPE animType, float maxX, float maxY,
		float startX, float startY, float endX, float endY, float limitTime)
	{
		pTexture = texture;
		eAnimType = animType;

		fMaxX = maxX;
		fMaxY = maxY;

		fStartX = startX;
		fStartY = startY;

		fCurX = 0.f;
		fCurY = 0.f;

		fEndX = endX;
		fEndY = endY;

		fAccumulatedTime = 0.f;
		fElapsedTime = 0.f;
		fLimitTime = limitTime;

		bIsEnd = false;
	}

	CTexture* pTexture;
	ANIMATION_TYPE eAnimType;

	// �� ����
	float fMaxX;
	float fMaxY;

	float fStartX;
	float fStartY;
	
	// ���� ��ġ
	float fCurX;
	float fCurY;

	float fEndX;
	float fEndY;

	// �ִϸ��̼� ����ð�
	float fAccumulatedTime;
	float fElapsedTime;
	float fLimitTime;

	// �ִϸ��̼� ���Ῡ��
	bool bIsEnd;
	
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
	MONSTER_TYPE monster_type;
	MONSTER_FIRETYPE fire_type;
	MONSTER_MOVETYPE move_type;
	int monster_various;

	int spawnPos_x;
	int spawnPos_y;
	int spawnTime;
}SPAWN_INFO;

#define __STRUCT_H__
#endif
