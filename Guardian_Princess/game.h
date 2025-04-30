#pragma once
#include "utils.h"
#include "unit.h"

// Todo: 1.UnitSpawner 초기화 함수 만들기 
//       2. UpdateSpawner(UnitSpawner*) 함수 만들기
//				- if active, then timer += dt
//							 if timer >= duration, then timer = 0, active = false
//					
typedef struct UnitSpawner
{
	float timer;
	float duration;
	int isActive;
} UnitSpawner;

void InitHero(void);

void InitUnit(void);

void SummonUnit(Unit* unit, UnitType type);

void DrawUnits(Unit* unit, CP_Image* unitani, int totalframe);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
