#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "unit.h"

typedef struct Hero
{
	Unit hero;
	int maxHP;
	float skillTimer;

}Hero;


void DrawHero(Hero hero1);
void InitHero(CP_Image* Motion1);
void UpdateHero(float dt);