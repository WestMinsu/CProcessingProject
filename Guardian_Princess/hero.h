#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "unit.h"

typedef struct Hero
{
	Unit hero;
	float skillTimer;

}Hero;


void DrawHero();
void InitHero(CP_Image* Motion1);
void UpdateHero(float dt);