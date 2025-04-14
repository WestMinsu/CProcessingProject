#pragma once

struct Circle
{
	CP_Vector position;
	double radius;
};

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
CP_BOOL timeElapsed(float seconds);
CP_BOOL circleToCircle(struct Circle a, struct Circle b);

//시간 저장하는 구조체

