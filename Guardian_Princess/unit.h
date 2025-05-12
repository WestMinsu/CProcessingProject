#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "constants.h"
#include "resource.h"
#include "FUNC_Animation_Motion.h"
#include "game.h"

extern int allyPopulation;
extern int enemyPopulation;

typedef struct AttackTimer
{
	float timer;
} AttackTimer;

enum UnitState
{
	ATTACK,
	WALK,
	DEAD,
	IDLE,
};

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
	float attackSpeed;
	int price;
	struct Unit* targetUnit;
	float attackTimer;

	AnimationState animationStateInfo;
	AnimationFrameInfo animationFrameInfo;
	enum UnitState state;
}Unit;

extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];


void InitUnit(void);
void SummonUnit(Unit* unit, UnitType type);
void UpdateUnits(float dt);

void DrawUnits(Unit* unit);
