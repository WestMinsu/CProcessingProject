#include <stdio.h>



int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	if (area_center_x - area_width / 2 < click_x && click_x < area_center_x + area_width / 2 && area_center_y - area_height / 2 < click_y && click_y < area_center_y + area_height / 2 && CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		return 1;

	return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	if ((click_x - circle_center_x) * (click_x - circle_center_x) + (click_y - circle_center_y) * (click_y - circle_center_y) < (diameter / 2) * (diameter / 2) && CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		return 1;

	return 0;
}

int Click_Button_Display(CP_image loaded_button_image, char type, float ButtonX, float ButtonY, float ButtonW, float ButtonH, int ButtonA)
//��ư �̹��� ǥ��, �Ҹ�, Ŭ���� �� ��ȣ�ۿ� ���� ���� Ŭ�� = 0 , ������ = 1 
{
	CP_Image_Draw(loaded_button_image, ButtonX + ButtonW / 2, ButtonY + ButtonH / 2, ButtonW, ButtonH, int ButtonA)

		if (type != 'c')
		{
			if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && IsAreaClicked(float ButtonX + ButtonW / 2, ButtonY + ButtonH / 2, ButtonW, ButtonH))
			{
				return int 0;
			}
			else (CP_Input_MouseReleased(MOUSE_BUTTON_RIGHT) && IsAreaClicked(float ButtonX + ButtonW / 2, ButtonY + ButtonH / 2, ButtonW, ButtonH))
			{
				return int 1;

			}
		}


}

