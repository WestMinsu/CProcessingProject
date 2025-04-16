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
	int speed;
	Circle collider;
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
	int speed;
	Circle collider;
	EnemyType type;
}Enemy;

typedef struct
{
	float timer;
} EnemySpawner;

void SummonAllyUnit(void);

void SummonEnemyUnit(EnemyType type);

void DrawAllyUnits(void);

void DrawEnemyUnits(void);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
