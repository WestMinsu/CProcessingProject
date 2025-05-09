#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "unit.h"

typedef struct Hero
{
	Unit hero;
	float skillTimer;
}Hero;

void InitHero(void);
void UpdateHero(float dt);
void DrawHero(void);