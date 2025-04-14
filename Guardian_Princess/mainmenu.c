#include <stdlib.h>
#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "asset_loading.h"

//------------------------내장 함수 불러오기-------------------------

extern CP_Image Main_Title_Image; //메인 이미지 재생
extern CP_Image cursorImage; // 커서 이미지
extern CP_Image button_start;// 테스트 버튼
extern CP_Image button_exit;
extern CP_Image Intro_digipen; //디지펜 로고
extern CP_Image Intro_teamlogo;//팀 로고 출력
extern CP_Image Intro_bic;//bic 로고 출력


extern CP_Sound Main_Title_Music;// 메인 음악 재생
extern CP_Sound Mouse_Click_Sound;// 마우스 클릭 음악 재생
extern CP_Sound button_sound;//


extern CP_Font mainTitleFont;// 메인 폰트 변경


//--------------------작동 여부 확인 트리거-----------------------------

void Main_Menu_Init(void)
{
	CP_System_SetWindowTitle("Guardian Princess"); //프로그램 창 이름
	CP_System_ShowCursor(FALSE);//커서 보이게 하기

	//--------------------------에셋 정의 및 로딩---------------------------

	sound_load();
	image_load();
	font_load();

	//-----------------------------음악 설정------------------------------

	CP_Sound_Play(Main_Title_Music);
}

void Main_Menu_Update(void)
{
	//------------------------------이미지 재생-----------------------------


	// 메인 배경 이미지
	float x = (float)CP_System_GetWindowWidth() / 2;
	float y = (float)CP_System_GetWindowHeight() / 2;
	float w = (float)CP_System_GetWindowWidth();
	float h = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(Main_Title_Image, x, y, w, h, 255);


	// 버튼
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
			CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
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

	// 커서 이미지
	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;
	CP_Image_Draw(cursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);


	//--------------------------마우스 클릭 관련 설정-----------------------------

}

void Main_Menu_Exit(void)
{
	//------------------------------이미지, 음악 종료---------------------------
	CP_Image_Free(&Main_Title_Image);
	CP_Sound_Free(&Main_Title_Music);
}