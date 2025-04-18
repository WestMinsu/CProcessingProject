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
	UnitType type;

	int hp;
	int attackDamage;
	float attackSpeed;
}Ally;

void SummonAllyUnit(UnitType type);
void DrawAllyUnits(void);