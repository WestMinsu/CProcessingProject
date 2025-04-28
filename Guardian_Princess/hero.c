#include "hero.h"
#include "colors.h"
#include "utils.h"
#include "unit.h"
#include "enemybase.h"

extern Hero hero;
extern Unit enemy[MAX_UNIT];
extern EnemyBase enemyBase;

void InitHero(void)
{
	hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
	hero.collider.radius = 30;
	hero.moveSpeed = 400;

	hero.maxHP = 1000;
	hero.currentHP = hero.maxHP;
	hero.attackDamage = 50;
	hero.attackCoolDown = 2;
	hero.attackRange.position = hero.position;
	hero.attackRange.radius = 50;
	hero.targetUnit = NULL;
}

void UpdateHero(float dt)
{
	if (CP_Input_KeyDown(KEY_A))
	{
		hero.position.x -= hero.moveSpeed * dt;
	}

	else if ((CP_Input_KeyDown(KEY_D)) && (!circleToCircle(hero.collider, enemyBase.collider)))
	{
		hero.position.x += hero.moveSpeed * dt;
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (circleToCircle(hero.collider, enemy[i].collider))
			{
				hero.position.x -= hero.moveSpeed * dt;
			}
		}
	}

	hero.collider.position = CP_Vector_Set(hero.position.x, hero.position.y);
	hero.attackRange.position = hero.collider.position;
}

void DrawHero(void)
{
	CP_Settings_Fill(green);
	CP_Graphics_DrawCircle(hero.position.x, hero.position.y, 30);
}