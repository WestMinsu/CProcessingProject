#include "cprocessing.h"
#include "FUNC_Button.h"


int Button_Draw_Square(CP_Image loaded_image, float buttonX, float buttonY, float buttonW, float buttonH, int buttonA) 
//x,y 중점의 사각형 모양의 버튼 만들기 (이미지 삽입 및 상호작용까지) 
{
	CP_Image_Draw(loaded_image, buttonX, buttonY, buttonW, buttonH, buttonA);
	
	if ((CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
	//마우스 왼쪽 버튼 눌렀을 때 0 반환
	{
		return 0;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_RIGHT)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
	//마우스 오른쪽 버튼 눌렀을 때 1반환
	{
		return 1;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_MIDDLE)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
	//마우스 가운데(스크롤) 버튼 눌렀을 때 2 반환
	{
		return 2;
	}
	else
	{
		return -1;
	}

}


int Button_Draw_Circle(CP_Image loaded_image, float buttonX, float buttonY, float buttonW, float buttonH, int buttonA)
//x,y 중점의 원형 모양의 버튼 만들기 - 사진은 원형으로 안 만들어줌 (원형 사진을 쓸 때 사용할 것) - 이미지 삽입 및 상호작용까지
{
	CP_Image_Draw(loaded_image, buttonX, buttonY, buttonW, buttonH, buttonA);

	if ((CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) && ((CP_Input_GetMouseX() - buttonX) * (CP_Input_GetMouseX() - buttonX) + (CP_Input_GetMouseY() - buttonY) * (CP_Input_GetMouseY() - buttonY) <= (buttonW / 2) * (buttonW / 2)))
		//마우스 왼쪽 버튼 눌렀을 때 0 반환 
	{
		return 0;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_RIGHT)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
		//마우스 오른쪽 버튼 눌렀을 때 1반환
	{
		return 1;
	}
	else if ((CP_Input_MouseReleased(MOUSE_BUTTON_MIDDLE)) && (buttonX - buttonW / 2 < CP_Input_GetMouseX()) && (buttonX + buttonW / 2 > CP_Input_GetMouseX()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()) && (buttonY - buttonH / 2 < CP_Input_GetMouseY()))
		//마우스 가운데(스크롤) 버튼 눌렀을 때 2 반환
	{
		return 2;
	}
	else
	{
		return -1;
	}
}