#pragma once
#include "cprocessing.h"

typedef struct Bomb
{
	CP_Vector position;
	int damage;
}Bomb;

Bomb bomb;

void InitBomb()
{
	bomb.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 8.0f);
	bomb.damage = 30;
}

void DrawBomb(float dt)
{
	CP_Image bombImage = CP_Image_Load("Assets/In_game/bomb.png");
	CP_Image_Draw(bombImage, bomb.position.x, bomb.position.y, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 8.0f, 255);
	printf("x = %lf, y = %lf", bomb.position.x, bomb.position.y);
	bomb.position.y += 100 * dt;
}