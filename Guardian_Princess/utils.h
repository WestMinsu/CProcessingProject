#pragma once
#include "cprocessing.h"

typedef struct UnitSpawner UnitSpawner;

typedef enum UnitType
{
	WARRIOR,
	ARCHER,
	HERO,
}UnitType;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
CP_BOOL SpawnTimeElapsed(UnitSpawner* enemySpawner, float time, UnitType type);
CP_BOOL AttackTimeElapsed(float* attackTimer, float time);

typedef struct Circle
{
	CP_Vector position;
	double radius;
}Circle;

CP_BOOL circleToCircle(Circle a, Circle b);