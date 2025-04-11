#include <math.h>
#include "cprocessing.h"

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

