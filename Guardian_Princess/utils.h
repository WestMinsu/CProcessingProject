#pragma once
#include "game.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
CP_BOOL timeElapsed(EnemySpawner* enemySpawner, float time, EnemyType type);
CP_BOOL circleToCircle(Circle a, Circle b);

//시간 저장하는 구조체

