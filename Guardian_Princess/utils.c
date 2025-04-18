#include "cprocessing.h"
#include "utils.h"
#include "game.h"

//디버깅용(삭제 예정)
#include <stdio.h>


int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{	
	if(area_center_x - area_width / 2 < click_x && click_x < area_center_x + area_width / 2 && area_center_y - area_height / 2 < click_y && click_y < area_center_y + area_height / 2 && CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		return 1;

	return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	if ((click_x - circle_center_x) * (click_x - circle_center_x) + (click_y - circle_center_y) * (click_y - circle_center_y) < (diameter / 2) * (diameter / 2) && CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		return 1;

	return 0;
}

CP_BOOL timeElapsed(EnemySpawner* enemySpawner, float time, EnemyType type)
{
	float dt = 0;
	dt = CP_System_GetDt();

	enemySpawner[type].timer += dt;
	if (enemySpawner[type].timer >= time)
	{
		enemySpawner[type].timer = 0;
		return TRUE;
	}
	else
		return FALSE;
}

CP_BOOL circleToCircle(Circle a, Circle b)
{
	if (a.radius <= 0 || b.radius <= 0)
		return FALSE;
	CP_Vector n = CP_Vector_Set(b.position.x - a.position.x, b.position.y - a.position.y);
	double r = a.radius + b.radius;
	double d = n.x * n.x + n.y * n.y; 
	//printf("r = %f, d = %f\n", r, d);
	if (r > 0 && d <= r * r) return TRUE;
	return FALSE;
}