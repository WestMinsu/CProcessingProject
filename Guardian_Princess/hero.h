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
void InitHero();
void UpdateHero(float dt);


extern CP_Image* heroAttack;
extern CP_Image* heroDead;
extern CP_Image* heroIdle;
extern CP_Image* heroWalk;