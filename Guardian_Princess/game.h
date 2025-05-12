#pragma once
#include "utils.h"
#include "unit.h"
#include "cprocessing.h"


typedef struct AllySpawner
{
	float timer;
<<<<<<< Updated upstream
} AllySpawner;


typedef struct EnemySpawner
{
	float timer;
} EnemySpawner;

void InitHero(void);

void InitUnit(void);

void SummonUnit(Unit* unit, UnitType type);

void DrawUnits(Unit* unit, CP_Image* unitani,int totalframe);

=======
	float duration;
	int isActive;
} UnitSpawner;





>>>>>>> Stashed changes
void GameInit(void);

void GameUpdate(void);

void GameExit(void);
