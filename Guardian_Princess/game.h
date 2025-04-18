#pragma once
#include "utils.h"

typedef enum 
{
	MELEE,
	RANGED,
}UnitType;

typedef struct
{
	float timer;
} AllySpawner;


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
