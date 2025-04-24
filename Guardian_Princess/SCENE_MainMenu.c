#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
//------------------------------------------------------------------------------------------------
#include "SCENE_MainMenu.h"
#include "game.h"
#include "asset_loading.h"
//------------------------------------------------------------------------------------------------
#include "FUNC_Button.h"
#include "FUNC_Animation_Motion.h"
//------------------------���� �ҷ�����-------------------------
CP_Sound Main_Title_Music;  // ���� Ÿ��Ʋ ����

CP_Image button_start;
CP_Image button_exit;
CP_Image Main_Title_Image;
//----------------------------------------------------------------

void MainMenuInit(void)
{
	//���� �ε� ----------------------------------------------------------------

	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3"); //���� Ÿ��Ʋ ����
	button_start = CP_Image_Load("Assets/main_title_assets/start.png");
	button_exit = CP_Image_Load("Assets/main_title_assets/exit.png");
	Main_Title_Image = CP_Image_Load("Assets/main_title_assets/title_image.png");

	CP_Sound_PlayAdvanced(Main_Title_Music, 0.8f, 1.0f, 1, BGM); //���� ���� ���� ���
}

void MainMenuUpdate(void)
{
	//�̹��� draw ---------------------------------------------


	CP_Image_Draw(Main_Title_Image, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255); // ���� ���
	int start_input = Button_Draw_Square(button_start, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	int exit_input = Button_Draw_Square(button_exit, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255); //Ŀ�� �̹���


	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	if (start_input == 0)
	{
		CP_Sound_PlayAdvanced(button_sound, 1.0f, 1.0f, 0, UI);
		CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
	}
	else if (exit_input == 0)
	{
		CP_Sound_PlayAdvanced(button_sound, 1.0f, 1.0f, 0, UI);
		CP_Engine_Terminate();
	}
	else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
	{
		CP_Sound_PlayAdvanced(Mouse_Click_Sound, 1.0f, 1.0f, 0, UI);
	}

}
void MainMenuExit(void)
{
	//���� ���� -------------------------------------------------------------------------------
	CP_Sound_Free(&Main_Title_Music);

	CP_Image_Free(&button_start);
	CP_Image_Free(&button_exit);
	CP_Image_Free(&Main_Title_Image);
}