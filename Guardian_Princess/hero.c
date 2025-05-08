#include "hero.h"
#include "colors.h"
#include "utils.h"
#include "unit.h"
#include "enemybase.h"
#include "FUNC_Animation_Motion.h"
//-----------
extern Hero hero;

//-----------------

extern CP_Image* heroAttack;
extern CP_Image* heroDead;
extern CP_Image* heroHurt;
extern CP_Image* heroWait;
extern CP_Image* heroWalk;

//-----------------

void InitHero(void)
{
	hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
	hero.collider.radius = 30;
	hero.moveSpeed = 400;

	hero.maxHP = 1000;
	hero.currentHP = hero.maxHP;
	hero.attackDamage = 1;
	hero.attackSpeed = 1;
	hero.attackRange.position = hero.position;
	hero.attackRange.radius = 50;
}

void UpdateHero(float dt)
{
	

	if (CP_Input_KeyDown(KEY_A))
	{
		hero.position.x -= hero.moveSpeed * dt;

	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		hero.position.x += hero.moveSpeed * dt;
	}
	hero.collider.position = CP_Vector_Set(hero.position.x, hero.position.y);
	hero.attackRange.position = hero.collider.position;
}

void DrawHero(void)
{
	Animation_play(heroWait,&hero.heroSetting, 5, 1, hero.position.x, hero.position.y, 128, 128, 255);

}