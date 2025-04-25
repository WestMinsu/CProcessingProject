#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_MainMenu.h"


#include "FUNC_BUTTON.h"

//------------------------------
CP_Image title_background;
CP_Image title_start_button;
CP_Image title_image;

CP_Sound title_start_sound;
CP_Sound Main_Title_Music;
//------------------------------

void MainTitleInit(void)
{
	//에셋 로딩 -----------------------------------------
	title_background = CP_Image_Load("Assets/MainTitle/title_background.png");
	title_start_button = CP_Image_Load("Assets/MainTitle/title_startButton.png");
	title_image = CP_Image_Load("Assets/MainTitle/title_image.png");

	title_start_sound = CP_Sound_Load("Assets/MainTitle/gameTitleStart.wav");
	Main_Title_Music = CP_Sound_Load("Assets/MainTitle/main_ost.mp3");


	CP_Sound_PlayAdvanced(Main_Title_Music, 0.8f, 1.0f, 1, BGM); //메인 음악 루프 재생
}


//---------------------------------------


void MainTitleUpdate(void)
{
	static int blinkCount = 0;
	static int blinkAlpha = 255;

	//이미지 draw ---------------------------------------------
	CP_Image_Draw(title_background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255); 
	CP_Image_Draw(title_image, CP_System_GetWindowWidth() / 5.0f*2.5f, CP_System_GetWindowHeight() / 4.0f*1.5f, CP_System_GetWindowWidth() / 2.5f, CP_System_GetWindowHeight() / 2.5f, 255); 
	CP_Image_Draw(title_start_button, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 8.0f * 7, CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 10.0f, blinkAlpha);
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255); //커서 이미지

	//------------------------------------------------------------------------------------------------------------------------
	
	
	
	blinkCount++;

	if (blinkCount == 50)
	{
		if (blinkAlpha == 255)
		{
			blinkAlpha = 0;
		}
		else if (blinkAlpha == 0)
		{
			blinkAlpha = 255;
		}
		blinkCount = 0;
	}
	//------------------------------------------------------------------------------------------------------------------------

	float titleCount = CP_System_GetSeconds();

	if (titleCount <= 6.0f && CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) || CP_Input_KeyReleased(KEY_SPACE))
	{
		CP_Sound_PlayAdvanced(title_start_sound, 1.0f, 1.0f, 0, UI);
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);

	}


}


void MainTitleExit(void)
{

	CP_Image_Free(&title_background);
	CP_Image_Free(&title_start_button);
	CP_Sound_Free(&Main_Title_Music);

	//CP_Sound_Free(&title_start_sound); TODO : 프리 할 시 스테이트 넘어가면 버튼 클릭 소리 안남 - 임시 조치
}