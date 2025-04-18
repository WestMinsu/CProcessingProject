#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"

//------------------------------------------------------------------------------------------------

#include "SCENE_MainMenu.h"
#include "utils.h"
#include "game.h"
#include "FUNC_Animation_Motion.h"
#include "asset_loading.h"

//------------------------���� �Լ� �ҷ�����-------------------------

CP_BOOL cursor = FALSE; // Ŀ�� ���̱� ���� ����

//------------------------���� �ҷ�����-------------------------

//# �ִϸ��̼� �� ��� ����

CP_Image* test11;
CP_Image* test12;

//## ����

CP_Sound Main_Title_Music;  // ���� Ÿ��Ʋ ����



//--------------------------------------------------------------------------------------------------------------------------------



void Main_Menu_Init(void)
{
	//���� �ε� ----------------------------------------------------------------

	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3"); //���� Ÿ��Ʋ ����
	image_load();
	sound_load();
	font_load();


	//TODO : ��Ʈ�η� ���� 
	CP_System_SetWindowTitle("Guardian Princess"); //���α׷� â �̸� 
	CP_System_ShowCursor(cursor);//Ŀ�� ���̰� �ϱ�

	// TODO : ���� ���� ���
	CP_Sound_Play(Main_Title_Music);

	test11 = Animation_ImageLoader("test3", 50); //test1 �̹��� �ε� 
	test12 = Animation_ImageLoader("test4", 50);
}




void Main_Menu_Update(void)
{



 //TODO : layer ����

	
	float x = (float)CP_System_GetWindowWidth() / 2;
	float y = (float)CP_System_GetWindowHeight() / 2;
	float w = (float)CP_System_GetWindowWidth();
	float h = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(Main_Title_Image, x, y, w, h, 255);

	Animation_play(test11, 50, TRUE, 500, 500, 500, 500, 255);
	Animation_play(test12, 50, TRUE, 1000, 500, 1000, 1000, 255);

	// ��ư
	float startButton_x = CP_System_GetWindowWidth() / 2.0f;
	float startButton_y = CP_System_GetWindowHeight() / 4.0f;
	float buttonWidth = CP_System_GetWindowWidth() / 8.0f;
	float buttonHeight = CP_System_GetWindowHeight() / 8.0f;
	CP_Image_Draw(button_start, startButton_x, startButton_y, buttonWidth, buttonHeight, 255);

	float exitButton_x = CP_System_GetWindowWidth() / 2.0f;
	float exitButton_y = CP_System_GetWindowHeight() / 4.0f * 3.0f;
	CP_Image_Draw(button_exit, exitButton_x, exitButton_y, buttonWidth, buttonHeight, 255);


	// Ŀ�� �̹���
	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;
	CP_Image_Draw(Cursor_image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);







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
			// TODO : terminate �Լ� ���� -> �ùٸ��� ���α׷� ����
			exit(0);
		}

		else
		{
			CP_Sound_Play(Mouse_Click_Sound);
		}
	}





}

void Main_Menu_Exit(void)
{
	
}