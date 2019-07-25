#pragma once

#ifndef __ENUM__H__

enum BULLET_BUTTON { BUTTON_A, BUTTON_S, BUTTON_END };
enum BULLET_DIRECTION { BULLET_LEFT, BULLET_RIGHT, BULLET_UP, BULLET_DOWN };
enum OBJECT_TYPE { OBJECT_STAGE, OBJECT_PLAYER, OBJECT_MONSTER, OBJLECT_BULLET, OBJECT_MONBULLET, OBJECT_WINGMAN, OBJECT_END };

enum PLAYER_MOVE_TYPE { PMT_LEFT3, PMT_LEFT2, PMT_LEFT1, PMT_DEFAULT, PMT_RIGHT1, PMT_RIGHT2, PMT_RIGHT3 };
enum SPAWN_LOCATION { LEFT_50, LEFT_150, LEFT_250, MIDDLE_350, RIGHT_450, RIGHT_550, RIGHT_650, LOCATION_END };

enum MONSTER_TYPE { DEFAULT, NORMAL, MIDDLE, BOSS, MONSTER_END };
enum MONSTER_FIRETYPE { SINGLE, BRUST_2, BRUST_3, AUTO };
enum MONSTER_MOVETYPE { DOWN, RIGHT, LEFT, TO_PLAYERX };

enum BULLET_TYPE { SMALL, MIDIUM, FAST, BOMB };

enum ANIMATION_TYPE { AT_LOOP, AT_RETAIN, AT_REVERSE_RETAIN, AT_END };

#define __ENUM__H__
#endif
