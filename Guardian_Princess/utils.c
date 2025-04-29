#include "cprocessing.h"
#include "utils.h"
#include "game.h"

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

CP_BOOL SpawnTimeElapsed(UnitSpawner* unitSpawner, float time, UnitType type)
{
	float dt = 0;
	dt = CP_System_GetDt();

	unitSpawner[type].timer += dt;
	if (unitSpawner[type].timer >= time)
	{
		unitSpawner[type].timer = 0;
		return TRUE;
	}
	else
		return FALSE;
}

CP_BOOL unitAttackTimeElapsed(AttackTimer* unitAttackTimer, float time, int index)
{
	float dt = CP_System_GetDt();

	unitAttackTimer[index].timer += dt;
	if (unitAttackTimer[index].timer >= time)
	{
		unitAttackTimer[index].timer = 0;
		return TRUE;
	}
	else
		return FALSE;
}

extern AttackTimer heroAttackTimer;
CP_BOOL heroAttackTimeElapsed(float time)
{
	float dt = 0;
	dt = CP_System_GetDt();

	heroAttackTimer.timer += dt;
	if (heroAttackTimer.timer >= time)
	{
		heroAttackTimer.timer = 0;
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
	if (r > 0 && d <= r * r) return TRUE;
	return FALSE;
}