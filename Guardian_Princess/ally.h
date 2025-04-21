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

	int price;
}Ally;

void SummonAllyUnit(UnitType type);
void UpdateAllyUnits(float dt);
void DrawAllyUnits(void);