#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "constants.h"
#include "resource.h"
#include "FUNC_Animation_Motion.h"

extern int allyPopulation;
extern int enemyPopulation;

typedef struct AttackTimer
{
	float timer;
} AttackTimer;

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
	AnimationFrameInfo unitSetting;
	struct Unit* targetUnit;
	float attackTimer;
	//float spawnTimer[NUM_UNIT_TYPES];
}Unit;

extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];

void InitUnit(void);
void SummonUnit(Unit* unit, UnitType type, AnimationDesc desc);
void UpdateUnits(float dt);
void DrawUnits(Unit* unit, int totalframe);


void UpdateHero(float dt);
