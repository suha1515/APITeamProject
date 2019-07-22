#pragma once

#ifndef __STRUCT_H__

typedef struct tagInfo
{
	float fX = 0.f;
	float fY = 0.f;
	float fCX = 0.f;
	float fCY = 0.f;
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

#define __STRUCT_H__
#endif
