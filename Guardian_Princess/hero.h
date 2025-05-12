#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "FUNC_Animation_Motion.h"
#include "game.h"

typedef struct Hero
{
	CP_Vector position;
	CP_BOOL alived;
	int moveSpeed;
	Circle collider;
	Circle attackRange;

	int maxHP;
	int currentHP;
	int attackDamage;

	float attackCoolDown;
	AnimationFrameInfo heroSetting;
	struct Unit* targetUnit;

}Hero;

void InitHero(void);
void DrawHero(enum UnitState state);
void UpdateHero(float dt);
