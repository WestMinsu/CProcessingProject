
#include "cprocessing.h"

//------------------------���� �Լ� �ҷ�����-------------------------

CP_Image Main_Title_Image; //���� �̹��� ���
CP_Image Cursor_image; // Ŀ�� �̹���
CP_Image button_test;// �׽�Ʈ ��ư

CP_Sound Main_Title_Music;// ���� ���� ���
CP_Sound Mouse_Click_Sound;// ���콺 Ŭ�� ���� ���
CP_Sound button_sound;//

CP_Font Main_Title_font;// ���� ��Ʈ ����

CP_BOOL cursor = FALSE; // Ŀ�� ���̱� ���� ����


//-------------------�Լ� �߰� ���� -----------------------------

		//���콺 Ŀ�� �۵�
void cursor_sound(float input_x1, float input_y1, float input_w1, float input_h1)
{	

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		if ((((CP_Input_GetMouseX() <= (input_x1 + (input_w1 * 0.5))) && (CP_Input_GetMouseX() >= (input_x1 - (input_w1 * 0.5)))) && ((CP_Input_GetMouseY() <= (input_y1 + (input_h1 * 0.5))) && (CP_Input_GetMouseY() >= (input_y1 - (input_h1 * 0.5))))))
		{

			CP_Sound_Play(button_sound);
		}
		else
		{
			CP_Sound_Play(Mouse_Click_Sound);

		}
	}
	
}




				

//--------------------�۵� ���� Ȯ�� Ʈ����-----------------------------







void game_init(void)
{
	CP_System_SetWindowTitle("Guardian Princess\n"); //���α׷� â �̸�
	CP_System_ShowCursor(cursor);//Ŀ�� ���̰� �ϱ�

	//--------------------------���� ���� �� �ε�---------------------------

	Main_Title_Image = CP_Image_Load("Assets/main_title_assets/download.png");
	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3");
	Main_Title_font = CP_Font_Load("Assets/fonts/DungGeunMo.ttf");
	button_test = CP_Image_Load("Assets/main_title_assets/start.png");
	Cursor_image = CP_Image_Load("Assets/mouse_settings/test_cursor.png");
	Mouse_Click_Sound = CP_Sound_Load("Assets/mouse_settings/test_mouseclick.mp3");
	button_sound = CP_Sound_Load("Assets/main_title_assets/test_button_sound.mp3");

	//-----------------------------���� ����------------------------------

	CP_Sound_Play(Main_Title_Music);

	
}


void game_update(void)
{

	//------------------------------�̹��� ���-----------------------------


		// ���� ��� �̹���
	float x = (float)CP_System_GetWindowWidth() / 2;
	float y = (float)CP_System_GetWindowHeight() / 2;
	float w = (float)CP_System_GetWindowWidth();
	float h = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(Main_Title_Image, x, y, w, h, 255);

	// ��ư �̹���

	CP_Image_Draw(button_test, 50, 50, 50, 50, 255);
	cursor_sound(50, 50, 50, 50);

	// Ŀ�� �̹���

	CP_Image_Draw(Cursor_image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 30, 30, 255);



	//--------------------------���콺 Ŭ�� ���� ����-----------------------------



}
void game_exit(void)
{

	//------------------------------�̹���, ���� ����---------------------------
	CP_Image_Free(&Main_Title_Image);
	CP_Sound_Free(&Main_Title_Music);
}


int main(void)
{
	//----------------------------������ ������ ũ�� ����---------------------------
	CP_System_SetWindowSize(1600, 800);


	//-------------------------------------------------------------------
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	
	return 0;
}
