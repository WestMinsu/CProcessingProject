#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "enemybase.h"
#include "colors.h"

extern EnemyBase enemyBase;
extern CP_Image enemyBaseImage;

void InitEnemyBase(void)
{
	enemyBase.position.x = CP_System_GetWindowWidth() / 5.0f * 4.4f;
	enemyBase.position.y = CP_System_GetWindowHeight() / 4.0f;
	enemyBase.maxHP = 1000;
	enemyBase.currentHP = enemyBase.maxHP;
}

void SummonEnemyBase(void)
{
	enemyBase.collider.position = CP_Vector_Set(enemyBase.position.x, enemyBase.position.y);
	enemyBase.collider.radius = 200;
}

void DrawEnemyBase(void)
{
	CP_Image_Draw(enemyBaseImage, enemyBase.position.x, enemyBase.position.y, (float)enemyBase.collider.radius, (float)enemyBase.collider.radius + 50, 255);
}