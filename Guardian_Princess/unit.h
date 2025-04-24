#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "constants.h"
#include "resource.h"

extern int allyPopulation;
extern int enemyPopulation;

typedef struct Unit
{
	CP_Vector position;
	CP_BOOL alived;
	int moveSpeed;
	Circle collider;
	Circle attackRange;
	UnitType type;

	int currentHP;
	int attackDamage;
	float attackCoolDown;
	int price;
	struct Unit* targetUnit;
}Unit;

extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];

void InitUnit(void);
void SummonUnit(Unit* unit, UnitType type);
void UpdateUnits(float dt);
void DrawUnits(Unit* unit);
