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

	int currentHP;
	int attackDamage;

	float attackSpeed;
	//float ATKSTART_SPD; 

	//int cost;
	//float prd_time;
}Enemy;

void SummonEnemyUnit(UnitType type);
void UpdateEnemyUnits(float dt);
void DrawEnemyUnits(void);