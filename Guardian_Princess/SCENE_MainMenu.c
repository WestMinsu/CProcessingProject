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
//------------------------에셋 불러오기-------------------------
CP_Sound Main_Menu_Music;  // 메인메뉴 음악

CP_Image button_start;
CP_Image button_exit;
CP_Image Main_Menu_background;
CP_Image Princess_Main;
//----------------------------------------------------------------

void MainMenuInit(void)
{
	//에셋 로딩 ----------------------------------------------------------------

	Main_Menu_Music = CP_Sound_Load("Assets/MainMenu/MainMenu_BGM.mp3"); 

	button_start = CP_Image_Load("Assets/MainMenu/start.png");
	button_exit = CP_Image_Load("Assets/MainMenu/exit.png");
	Main_Menu_background = CP_Image_Load("Assets/MainMenu/MainMenuBG.png");
	Princess_Main = CP_Image_Load("Assets/MainMenu/MainPrincess.png");

	CP_Sound_PlayAdvanced(Main_Menu_Music, 0.8f, 1.0f, 1, BGM); //메인 음악 루프 재생
}

void MainMenuUpdate(void)
{
	int start_input = SquareButtonClicked(button_start, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	int exit_input = SquareButtonClicked(button_exit, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	int princess_click = SquareButtonClicked(Princess_Main, CP_System_GetWindowWidth() / 8.0f * 3, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 4.0f, CP_System_GetWindowWidth() * 0.8f, 255);

	//이미지 draw ---------------------------------------------
	CP_Image_Draw(Main_Menu_background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255); // 메인 배경
	CP_Image_Draw(button_start, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(button_exit, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(Princess_Main, CP_System_GetWindowWidth() / 8.0f * 1.5f, CP_System_GetWindowHeight() / 2.0f * 1.08f, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowWidth() * 0.5f, 255); //커서 이미지
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255); //커서 이미지



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

	if (princess_click == 0)
	{
		CP_Sound_PlayAdvanced(button_sound, 1.0f, 1.0f, 0, UI);
	}




}
void MainMenuExit(void)
{
	//에셋 프리 -------------------------------------------------------------------------------
	CP_Sound_Free(&Main_Menu_Music);

	CP_Image_Free(&button_start);
	CP_Image_Free(&button_exit);
	CP_Image_Free(&Main_Menu_background);

}