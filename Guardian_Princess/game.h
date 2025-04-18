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
}Ally;

typedef struct
{
	float timer;
} AllySpawner;

typedef enum{
	MELEE,
	RANGED,
}EnemyType;

typedef struct
{
	CP_Vector position;
	CP_BOOL alived;
	int moveSpeed;
	Circle collider;
	Circle attackRange;
	EnemyType type;

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

void SummonAllyUnit(void);

void SummonEnemyUnit(EnemyType type);

void DrawAllyUnits(void);

void DrawEnemyUnits(void);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
