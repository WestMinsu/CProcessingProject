#pragma once
#include "utils.h"
#include "unit.h"
#include "cprocessing.h"


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





void GameInit(void);

void GameUpdate(void);

void GameExit(void);
