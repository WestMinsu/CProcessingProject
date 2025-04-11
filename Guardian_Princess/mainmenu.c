#include <stdlib.h>
#include "cprocessing.h"
#include "utils.h"
#include "game.h"

//------------------------���� �Լ� �ҷ�����-------------------------

CP_Image Main_Title_Image; //���� �̹��� ���
CP_Image Cursor_image; // Ŀ�� �̹���
CP_Image button_start;// �׽�Ʈ ��ư
CP_Image button_exit;

CP_Sound Main_Title_Music;// ���� ���� ���
CP_Sound Mouse_Click_Sound;// ���콺 Ŭ�� ���� ���
CP_Sound button_sound;//

CP_Font Main_Title_font;// ���� ��Ʈ ����

CP_BOOL cursor = FALSE; // Ŀ�� ���̱� ���� ����



//--------------------�۵� ���� Ȯ�� Ʈ����-----------------------------

void Main_Menu_Init(void)
{
	CP_System_SetWindowTitle("Guardian Princess\n"); //���α׷� â �̸�
	CP_System_ShowCursor(cursor);//Ŀ�� ���̰� �ϱ�

	//--------------------------���� ���� �� �ε�---------------------------

	Main_Title_Image = CP_Image_Load("Assets/main_title_assets/download.png");
	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3");
	Main_Title_font = CP_Font_Load("Assets/fonts/DungGeunMo.ttf");
	button_start = CP_Image_Load("Assets/main_title_assets/start.png");
	button_exit = CP_Image_Load("Assets/main_title_assets/exit.png");
	Cursor_image = CP_Image_Load("Assets/mouse_settings/test_cursor.png");
	Mouse_Click_Sound = CP_Sound_Load("Assets/mouse_settings/test_mouseclick.mp3");
	button_sound = CP_Sound_Load("Assets/main_title_assets/test_button_sound.mp3");

	//-----------------------------���� ����------------------------------

	CP_Sound_Play(Main_Title_Music);
}

void Main_Menu_Update(void)
{
	//------------------------------�̹��� ���-----------------------------


	// ���� ��� �̹���
	float x = (float)CP_System_GetWindowWidth() / 2;
	float y = (float)CP_System_GetWindowHeight() / 2;
	float w = (float)CP_System_GetWindowWidth();
	float h = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(Main_Title_Image, x, y, w, h, 255);


	// ��ư
	float startButton_x = CP_System_GetWindowWidth() / 2.0f;
	float startButton_y = CP_System_GetWindowHeight() / 4.0f;
	float buttonWidth = CP_System_GetWindowWidth() / 8.0f;
	float buttonHeight = CP_System_GetWindowHeight() / 8.0f;
	CP_Image_Draw(button_start, startButton_x, startButton_y, buttonWidth, buttonHeight, 255);

	float exitButton_x = CP_System_GetWindowWidth() / 2.0f;
	float exitButton_y = CP_System_GetWindowHeight() / 4.0f * 3.0f;
	CP_Image_Draw(button_exit, exitButton_x, exitButton_y, buttonWidth, buttonHeight, 255);


	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
	{
		if (IsAreaClicked(startButton_x, startButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_Play(button_sound);
			CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
		}

		else if (IsAreaClicked(exitButton_x, exitButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_Play(button_sound);
			exit(0);
		}

		else
		{
			CP_Sound_Play(Mouse_Click_Sound);
		}
	}

	// Ŀ�� �̹���
	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;
	CP_Image_Draw(Cursor_image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);


	//--------------------------���콺 Ŭ�� ���� ����-----------------------------

}

void Main_Menu_Exit(void)
{
	//------------------------------�̹���, ���� ����---------------------------
	CP_Image_Free(&Main_Title_Image);
	CP_Sound_Free(&Main_Title_Music);
}