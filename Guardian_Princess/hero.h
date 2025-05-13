#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "unit.h"

typedef struct Hero
{
	Unit hero;
	float skillTimer;

}Hero;


void DrawHero(enum UnitState state);
void InitHero();
void UpdateHero(float dt);