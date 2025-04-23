#pragma once
#include "utils.h"
#include "unit.h"

typedef struct AllySpawner
{
	float timer;
} AllySpawner;


typedef struct EnemySpawner
{
	float timer;
} EnemySpawner;

void InitHero(void);

void InitUnit(void);

void SummonUnit(Unit* unit, UnitType type);

void DrawUnits(Unit* unit);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
