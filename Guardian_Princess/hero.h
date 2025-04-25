#pragma once
#include "cprocessing.h"
#include "utils.h"

typedef struct
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
	struct Unit* targetUnit;
}Hero;

void InitHero(void);
void UpdateHero(float dt);
void DrawHero(void);