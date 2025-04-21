#pragma once
#include "UNIT_Enemy.h"

typedef struct EnemySpawner EnemySpawner;


CP_BOOL timeElapsed(EnemySpawner* enemySpawner, float time, UnitType type);

typedef struct
{
	CP_Vector position;
	double radius;
}Circle;

CP_BOOL circleToCircle(Circle a, Circle b);