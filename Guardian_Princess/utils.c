#include <math.h>
#include "cprocessing.h"
#include "utils.h"

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

CP_BOOL timeElapsed(float seconds)
{
	float currentElapsedTime = 0;

	currentElapsedTime = CP_System_GetDt();
	static float totalElapsedTime = 0;
	totalElapsedTime += currentElapsedTime;
	if (totalElapsedTime >= seconds)
		return TRUE;
	else
		return FALSE;
}


CP_BOOL circleToCircle(struct Circle a, struct Circle b)
{
	CP_Vector n = CP_Vector_Set(b.position.x - a.position.x, b.position.y - a.position.y);
	double r = a.radius + b.radius;
	double d = n.x * n.x + n.y * n.y; 
	printf("r = %f, d = %f\n", r, d);
	if (r > 0 && d <= r * r) return TRUE;
	return FALSE;
}