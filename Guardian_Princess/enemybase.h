#pragma once
#include "cprocessing.h"
#include "utils.h"

typedef struct
{
	CP_Vector position;
	CP_BOOL alived;
	Circle collider;

	int maxHP;
	int currentHP;
}EnemyBase;

void InitEnemyBase(void);
void SummonEnemyBase(void);
void DrawEnemyBase(void);