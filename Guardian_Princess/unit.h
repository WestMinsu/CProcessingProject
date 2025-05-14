#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "constants.h"
#include "resource.h"
#include "FUNC_Animation_Motion.h"

extern int allyPopulation;
extern int enemyPopulation;


extern CP_Image* heroAttack;
extern CP_Image* heroDead;
extern CP_Image* heroHurt;
extern CP_Image* heroIdle;
extern CP_Image* heroWalk;

extern CP_Image* allyArcherAttack; //8
extern CP_Image* allyArcherDead; //18
extern CP_Image* allyArcherIdle;//22
extern CP_Image* allyArcherWalk;//16

extern CP_Image* allyWarriorAttack;//8
extern CP_Image* allyWarriorDead;//21
extern CP_Image* allyWarriorIdle;//13
extern CP_Image* allyWarriorWalk;//14

extern CP_Image* enemyArcherAttack;///19
extern CP_Image* enemyArcherDead;//20
extern CP_Image* enemyArcherIdle;//11
extern CP_Image* enemyArcherWalk;//15

extern CP_Image* enemyWarriorAttack;//15
extern CP_Image* enemyWarriorDead;//20
extern CP_Image* enemyWarriorIdle;//14
extern CP_Image* enemyWarriorWalk;//4


enum UnitState
{
	ATTACK,
	WALK,
	DEAD,
	IDLE
};

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

	int maxHP;
	int currentHP;
	int attackDamage;
	float attackCoolDown;
	int price;
	
	struct Unit* targetUnit;
	float attackTimer;

	AnimationFrameInfo animationFrameInfo;
	AnimationState animationStateInfo;
	enum UnitState state;

}Unit;

extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];

void InitUnit(void);
void SummonUnit(Unit* unit, UnitType type);
void UpdateUnits(float dt);
void DrawUnits(Unit* unit);


void UpdateHero(float dt);
