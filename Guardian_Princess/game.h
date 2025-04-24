#pragma once
#include "utils.h"
#include "unit.h"

typedef struct UnitSpawner
{
	float timer;
} UnitSpawner;

typedef struct AttackTimer
{
	float timer;
} AttackTimer;

void InitHero(void);

void InitUnit(void);

void SummonUnit(Unit* unit, UnitType type);

void DrawUnits(Unit* unit);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
