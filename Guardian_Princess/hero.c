#include "hero.h"
#include "colors.h"
#include "utils.h"
#include "unit.h"
#include "enemybase.h"
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"

Hero hero1;
extern Unit enemy[MAX_UNIT];
extern EnemyBase enemyBase;

void InitHero(CP_Image* Motion1)
{
	hero1.hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 4.0f);
	hero1.hero.alived = TRUE;
	hero1.hero.moveSpeed = 400;
	hero1.hero.collider.radius = 30;
	hero1.hero.attackRange.position = hero1.hero.position;
	hero1.hero.attackRange.radius = 50;
		
	hero1.maxHP = 1000;
	hero1.hero.currentHP = hero1.maxHP;
	hero1.hero.attackDamage = 10;
	hero1.hero.attackCoolDown = 0.5f;
	hero1.hero.targetUnit = NULL;
	hero1.hero.attackTimer = 0;
	hero1.skillTimer = 0;

	hero1.hero.unitSetting.images = Motion1;

}

void UpdateHero(float dt)
{
	if (CP_Input_KeyDown(KEY_A))
	{
		hero1.hero.position.x -= hero1.hero.moveSpeed * dt;
		if (hero1.hero.position.x <= 100)
		{
			hero1.hero.position.x += hero1.hero.moveSpeed * dt;
		}
	}

	else if ((CP_Input_KeyDown(KEY_D)) && (!circleToCircle(hero1.hero.collider, enemyBase.collider)))
	{
		hero1.hero.position.x += hero1.hero.moveSpeed * dt;
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (enemy[i].alived && circleToCircle(hero1.hero.collider, enemy[i].collider))
			{
				hero1.hero.position.x -= hero1.hero.moveSpeed * dt;
			}
		}
	}

	hero1.hero.collider.position = CP_Vector_Set(hero1.hero.position.x, hero1.hero.position.y);
	hero1.hero.attackRange.position = hero1.hero.collider.position;
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

