#pragma once

typedef struct
{
	CP_Vector position;
	double radius;
}Circle;

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

typedef enum 
{
	MELEE,
	RANGED,
}UnitType;

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

typedef struct
{
	float timer;
} AllySpawner;


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
	//float ATKSTART_SPD; 

	//int cost;
	//float prd_time;
}Enemy;

typedef struct
{
	float timer;
} EnemySpawner;

void initHero(void);

void initUnit(void);

void SummonAllyUnit(UnitType type);

void SummonEnemyUnit(UnitType type);

void DrawAllyUnits(void);

void DrawEnemyUnits(void);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
