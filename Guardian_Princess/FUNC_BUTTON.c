#include "cprocessing.h"
#include "FUNC_Button.h"


int Button_Draw_Square(CP_Image loaded_image, float buttonX, float buttonY, float buttonW, float buttonH, int buttonA)
{
	CP_Image_Draw(loaded_image, buttonX, buttonY, buttonW, buttonH, buttonA);

	if ((CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY + buttonH / 2 > CP_Input_GetMouseY()))
	{
		return 0;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_RIGHT)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY + buttonH / 2 > CP_Input_GetMouseY()))
	{
		return 1;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_MIDDLE)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY + buttonH / 2 > CP_Input_GetMouseY()))
	{
		return 2;
	}
	else
	{
		return -1;
	}
}


int Button_Draw_Circle(CP_Image loaded_image, float buttonX, float buttonY, float buttonW, float buttonH, int buttonA)
{
	CP_Image_Draw(loaded_image, buttonX, buttonY, buttonW, buttonH, buttonA);

	if ((CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) && ((CP_Input_GetMouseX() - buttonX) * (CP_Input_GetMouseX() - buttonX) + (CP_Input_GetMouseY() - buttonY) * (CP_Input_GetMouseY() - buttonY) <= (buttonW / 2) * (buttonW / 2)))
	{
		return 0;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_RIGHT)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
	{
		return 1;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_MIDDLE)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

