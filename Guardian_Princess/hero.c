#include "hero.h"
#include "colors.h"
#include "globals.h"


extern Hero hero;
void InitHero(void)
{
	hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
	hero.collider.radius = 30;
	hero.moveSpeed = 400;

	hero.hp = 1000;
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
	CP_Settings_Fill(green);
	CP_Graphics_DrawCircle(hero.position.x, hero.position.y, 30);
}