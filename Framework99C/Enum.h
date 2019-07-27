#pragma once

#ifndef __ENUM__H__

enum BULLET_BUTTON { BUTTON_A, BUTTON_S, BUTTON_END };
enum BULLET_DIRECTION { BULLET_LEFT, BULLET_RIGHT, BULLET_UP, BULLET_DOWN };
enum OBJECT_TYPE { OBJECT_STAGE, OBJECT_PLAYER, OBJECT_MONSTER, OBJLECT_BULLET, OBJECT_MONBULLET, OBJECT_WINGMAN,OBJECT_ITEM, OBJECT_UI, OBJECT_END };

enum ITEM_TYPE {POWER,SPECIAL};

enum PLAYER_MOVE_TYPE { PMT_LEFT3, PMT_LEFT2, PMT_LEFT1, PMT_DEFAULT, PMT_RIGHT1, PMT_RIGHT2, PMT_RIGHT3 };
enum PLAYER_BULLET_TYPE{LEVEL1,LEVEL2,LEVEL3,LEVEL4,WINGMAN,LEVEL_END};

enum SPAWN_LOCATION { LEFT_50, LEFT_150, LEFT_250, MIDDLE_350, RIGHT_450, RIGHT_550, RIGHT_650, LOCATION_END };

enum MONSTER_TYPE { DEFAULT, NORMAL, MIDDLE, BOSS, MONSTER_END };

// MONSTER_TYPE: NORMAL
enum MONSTER_FIRETYPE { SINGLE, BRUST_2, BRUST_3, AUTO, BOMBING };
enum MONSTER_MOVETYPE { DOWN, RIGHT, LEFT, TO_PLAYERX, WAVING };

// MONSTER_TYPE: MIDDLE
enum MONSTER_FIRETYPE2 { AUTO2, BURST2, SWEEP2, VULCAN2 };
enum MONSTER_MOVETYPE2 { DOWN2, TO_PLAYER2 };

enum BULLET_TYPE { SMALL, MIDIUM, FAST, BOMB, SLOW };

enum ANIMATION_TYPE { AT_LOOP, AT_RETAIN, AT_ONCE_DESTROY, AT_END };

enum EFFECT {E_MINIPLANE_DESTROIED, E_END};

#define __ENUM__H__
#endif
