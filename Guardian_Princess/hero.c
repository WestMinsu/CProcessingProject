#include "hero.h"
#include "colors.h"
#include "utils.h"
#include "unit.h"
#include "enemybase.h"

Hero hero;
extern Unit enemy[MAX_UNIT];
extern EnemyBase enemyBase;

void InitHero(void)
{
	hero.hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 4.0f);
	hero.hero.alived = TRUE;
	hero.hero.moveSpeed = 400;
	hero.hero.collider.radius = 30;
	hero.hero.attackRange.position = hero.hero.position;
	hero.hero.attackRange.radius = 50;
	
	hero.maxHP = 100;
	hero.hero.currentHP = hero.maxHP;
	hero.hero.attackDamage = 50;
	hero.hero.attackCoolDown = 1.0f;
	hero.hero.targetUnit = NULL;
	hero.hero.attackTimer = 0;
}

void UpdateHero(float dt)
{
	if (CP_Input_KeyDown(KEY_A))
	{
		hero.hero.position.x -= hero.hero.moveSpeed * dt;
		if (hero.hero.position.x <= 100)
		{
			hero.hero.position.x += hero.hero.moveSpeed * dt;
		}
	}

	else if ((CP_Input_KeyDown(KEY_D)) && (!circleToCircle(hero.hero.collider, enemyBase.collider)))
	{
		hero.hero.position.x += hero.hero.moveSpeed * dt;
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (enemy[i].alived && circleToCircle(hero.hero.collider, enemy[i].collider))
			{
				hero.hero.position.x -= hero.hero.moveSpeed * dt;
			}
		}
	}

	hero.hero.collider.position = CP_Vector_Set(hero.hero.position.x, hero.hero.position.y);
	hero.hero.attackRange.position = hero.hero.collider.position;
}

void DrawHero(void)
{
	CP_Settings_Fill(green);
	CP_Graphics_DrawCircle(hero.hero.position.x, hero.hero.position.y, 30);
}