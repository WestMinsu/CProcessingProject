#pragma once
#include "utils.h"
#include "unit_info.h"

typedef struct 
{
	float timer;
} AllySpawner;


typedef struct EnemySpawner
{
	float timer;
} EnemySpawner;

void InitHero(void);

void initUnit(void);

void SummonAllyUnit(UnitType type);

void SummonEnemyUnit(UnitType type);

void DrawAllyUnits(void);

void DrawEnemyUnits(void);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
