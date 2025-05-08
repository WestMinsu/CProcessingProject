#pragma once
#include "cprocessing.h"


typedef struct Bomb
{
	CP_Vector position;
	CP_BOOL alived;
	int damage;
	float coolDown;
}Bomb;

extern Bomb bomb;

void InitBomb();
void SummonBomb();
void DrawBomb(float dt);