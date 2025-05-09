#pragma once
#include "utils.h"
#include "unit.h"

// Todo: 1.UnitSpawner �ʱ�ȭ �Լ� ����� 
//       2. UpdateSpawner(UnitSpawner*) �Լ� �����
//				- if active, then timer += dt
//							 if timer >= duration, then timer = 0, active = false
//					
typedef struct UnitSpawner
{
	float timer;
	float duration;
	int isActive;
} UnitSpawner;


extern CP_Image* heroAttack;
extern CP_Image* heroDead;
extern CP_Image* heroHurt;
extern CP_Image* heroWait;
extern CP_Image* heroWalk;





void InitUnit(void);

void DrawUnits(Unit* unit, int totalframe);

void GameInit(void);

void GameUpdate(void);

void GameExit(void);
