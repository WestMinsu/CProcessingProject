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

	int hp;
	int attackDamage;
	float attackSpeed;
}Hero;

void initHero(void);
void DrawHero(void);