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
//# 애니메이션 및 모션 에셋
//## 사운드
CP_Sound Main_Title_Music;  // 메인 타이틀 음악
//### 이미지 에셋
CP_Image button_start;
CP_Image button_exit;
CP_Image Main_Title_Image;

struct MainMenuGameState
{
	CP_Sound Main_Title_Music;
};

static struct MainMenuGameState mainmenu_gamestate;

void MainMenuInit(void)
{
//에셋 로딩 ----------------------------------------------------------------

	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3"); //메인 타이틀 음악
	button_start = CP_Image_Load("Assets/main_title_assets/start.png");
	button_exit = CP_Image_Load("Assets/main_title_assets/exit.png");
	Main_Title_Image = CP_Image_Load("Assets/main_title_assets/title_image.png");
	CP_Sound_PlayMusic(Main_Title_Music); //메인 음악 루프 재생
	mainmenu_gamestate.Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3"); //메인 타이틀 음악
	image_load();
	sound_load();
	font_load();


	//TODO : 인트로로 뺴기 
	CP_System_SetWindowTitle("Guardian Princess"); //프로그램 창 이름 
	CP_System_ShowCursor(FALSE);//커서 보이게 하기

	// TODO : 음악 루프 재생
	CP_Sound_Play(mainmenu_gamestate.Main_Title_Music);

	//test11 = Animation_ImageLoader("test3", 50); //test1 이미지 로딩 
	//test12 = Animation_ImageLoader("test4", 50);
}

void MainMenuUpdate(void)
{
	//이미지 draw ---------------------------------------------
	//# 단순 이미지
		CP_Image_Draw(Main_Title_Image, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth()/1.0f, CP_System_GetWindowHeight()/1.0f, 255); // 메인 배경
		CP_Image_Draw(Cursor_Image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight()/20.0f, 255); //커서 이미지
	//## 버튼 추가 및 이미지
		int start_input = Button_Draw_Square(button_start, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
		int exit_input = Button_Draw_Square(button_exit, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f*3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------


		if (start_input == 0)
		{
			CP_Sound_Play(button_sound);
			CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
		}
		else if (exit_input == 0)
		{
			CP_Sound_Play(button_sound);
			CP_Engine_Terminate();
		}
		else
		{
			CP_Sound_Play(Mouse_Click_Sound);
		}
}

void MainMenuExit(void)
{

	//에셋 프리 -------------------------------------------------------------------------------
	CP_Sound_Free(&Main_Title_Music);

	CP_Image_Free(&button_start);
	CP_Image_Free(&button_exit);
	CP_Image_Free(&Main_Title_Image);
}