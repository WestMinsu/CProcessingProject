#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"

//------------------------------------------------------------------------------------------------

#include "SCENE_MainMenu.h"
#include "utils.h"
#include "game.h"
#include "FUNC_Animation_Motion.h"
#include "asset_loading.h"

//------------------------내장 함수 불러오기-------------------------

CP_BOOL cursor = FALSE; // 커서 보이기 유무 설정

//------------------------에셋 불러오기-------------------------

//# 애니메이션 및 모션 에셋

CP_Image* test11;
CP_Image* test12;

//## 사운드

CP_Sound Main_Title_Music;  // 메인 타이틀 음악



//--------------------------------------------------------------------------------------------------------------------------------



void Main_Menu_Init(void)
{
	//에셋 로딩 ----------------------------------------------------------------

	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3"); //메인 타이틀 음악
	image_load();
	sound_load();
	font_load();


	//TODO : 인트로로 뺴기 
	CP_System_SetWindowTitle("Guardian Princess"); //프로그램 창 이름 
	CP_System_ShowCursor(cursor);//커서 보이게 하기

	// TODO : 음악 루프 재생
	CP_Sound_Play(Main_Title_Music);

	test11 = Animation_ImageLoader("test3", 50); //test1 이미지 로딩 
	test12 = Animation_ImageLoader("test4", 50);
}




void Main_Menu_Update(void)
{



 //TODO : layer 구현

	
	float x = (float)CP_System_GetWindowWidth() / 2;
	float y = (float)CP_System_GetWindowHeight() / 2;
	float w = (float)CP_System_GetWindowWidth();
	float h = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(Main_Title_Image, x, y, w, h, 255);

	Animation_play(test11, 50, TRUE, 500, 500, 500, 500, 255);
	Animation_play(test12, 50, TRUE, 1000, 500, 1000, 1000, 255);

	// 버튼
	float startButton_x = CP_System_GetWindowWidth() / 2.0f;
	float startButton_y = CP_System_GetWindowHeight() / 4.0f;
	float buttonWidth = CP_System_GetWindowWidth() / 8.0f;
	float buttonHeight = CP_System_GetWindowHeight() / 8.0f;
	CP_Image_Draw(button_start, startButton_x, startButton_y, buttonWidth, buttonHeight, 255);

	float exitButton_x = CP_System_GetWindowWidth() / 2.0f;
	float exitButton_y = CP_System_GetWindowHeight() / 4.0f * 3.0f;
	CP_Image_Draw(button_exit, exitButton_x, exitButton_y, buttonWidth, buttonHeight, 255);


	// 커서 이미지
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
			// TODO : terminate 함수 참조 -> 올바르게 프로그램 종료
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