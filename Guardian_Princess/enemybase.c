#pragma once
#include "cprocessing.h"
#include "utils.h"
#include "enemybase.h"
#include "colors.h"

extern EnemyBase enemyBase;

void InitEnemyBase(void)
{
	enemyBase.position.x = CP_System_GetWindowWidth() / 5.0f * 4.4f;
	enemyBase.position.y = CP_System_GetWindowHeight() / 8.0f;
	enemyBase.maxHP = 1000;
	enemyBase.currentHP = enemyBase.maxHP;
}

void SummonEnemyBase(void)
{
	enemyBase.collider.position = CP_Vector_Set(enemyBase.position.x, enemyBase.position.y);
	enemyBase.collider.radius = 250;
}

void DrawEnemyBase(void)
{
	CP_Settings_Fill(white);
	CP_Graphics_DrawRect(enemyBase.position.x, enemyBase.position.y, (float)enemyBase.collider.radius - 50, (float)enemyBase.collider.radius);
}