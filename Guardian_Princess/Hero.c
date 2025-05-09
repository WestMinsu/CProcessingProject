#include "hero.h"
#include "colors.h"
#include "utils.h"
#include "unit.h"
#include "enemybase.h"
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"

Hero hero;
extern Unit enemy[MAX_UNIT];
extern EnemyBase enemyBase;

void InitHero(CP_Image* Motion1)
{
	hero.hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 4.0f);
	hero.hero.alived = TRUE;
	hero.hero.moveSpeed = 400;
	hero.hero.collider.radius = 30;
	hero.hero.attackRange.position = hero.hero.position;
	hero.hero.attackRange.radius = 50;
		
	hero.maxHP = 1000;
	hero.hero.currentHP = hero.maxHP;
	hero.hero.attackDamage = 10;
	hero.hero.attackCoolDown = 0.5f;
	hero.hero.targetUnit = NULL;
	hero.hero.attackTimer = 0;
	hero.skillTimer = 0;

	hero.hero.unitSetting.images = Motion1;

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

void DrawHero(Hero hero2)
{
	Animation_play(hero2.hero.unitSetting.images, &hero2.hero.unitSetting, hero2.hero.unitSetting.totalframe, 1, hero2.hero.position.x, hero2.hero.position.y, 256, 256, 255);
}
//void DrawHeroAttack()
//{
//
//
//}
//void DrawHeroMove()
//{
//
//
//}
//void DrawHeroDead()
//{
//
//	CP_Graphics_DrawCircle(hero.hero.position.x, hero.hero.position.y, 30);
//}

