#include "skill.h"

Bomb bomb;
extern CP_Vector cameraPos;

void InitBomb()
{
	bomb.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 8.0f);
	bomb.alived = FALSE;
	bomb.damage = 300;
	bomb.coolDown = 15.0f;
}

void SummonBomb()
{
	bomb.position = CP_Vector_Set(cameraPos.x, CP_System_GetWindowHeight() / 8.0f);
	bomb.damage = 300;
	bomb.alived = TRUE;
}

void DrawBomb(float dt)
{
	if (bomb.alived)
	{
		CP_Image bombImage = CP_Image_Load("Assets/In_game/bomb.png");
		CP_Image_Draw(bombImage, bomb.position.x, bomb.position.y, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 8.0f, 255);
		bomb.position.y += 100 * dt;
	}
}