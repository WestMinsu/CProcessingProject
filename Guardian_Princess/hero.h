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

<<<<<<< Updated upstream
void InitHero(void);
void UpdateHero(float dt);
void DrawHero(void);
=======

void DrawHero(enum UnitState state);
void InitHero();
void UpdateHero(float dt);
>>>>>>> Stashed changes
