#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_Intro.h"
#include "SCENE_MainMenu.h"
#include "SCENE_MainTitle.h"
//에셋 로딩------------------------------------------------------------------------------------------------
CP_Sound LogoSong;
CP_Image DigipenLogo;
CP_Image LogoImage;
//--페이드 인, 아웃 관리------

//--------------

void GamePreUpdate(void)
{
	ImageLoad();
	SoundLoad();
	FontLoad();
	CP_System_ShowCursor(FALSE);
}


void IntroInit(void)
{
	CP_Engine_SetPreUpdateFunction(GamePreUpdate); //프리 스테이트 설정
	//게임 초기 시스템 설정--------------------------------
	CP_System_SetWindowTitle("Guardian Princess"); //프로그램 창 이름 
	CP_Settings_ImageMode(CP_POSITION_CENTER); //이미지 중점 가운데로 설정.
	CP_Color Default_BG = CP_Color_Create(0, 0, 0, 255);
	CP_Graphics_ClearBackground(Default_BG); //기본 배경 설정
	//에셋 로딩--------------------------------

	LogoSong = CP_Sound_Load("Assets/Intro/frostbyte_logo.mp3");
	LogoImage = CP_Image_Load("Assets/Intro/logo_image.png");
	DigipenLogo = CP_Image_Load("Assets/Intro/Digipen_logo.png");
}

void IntroUpdate(void)
{

	static int introAlpha = 0; // 화면 트랜지션 (알파값 조정)
	static int fadeSlow = 0; //화면 트랜지션 속도 관리 
	static int IsAudioPlayed = FALSE; // 오디오 한번만 재생 
	static int Introskip = 0; //클릭시 인트로 스킵 확인 변수


	float introCount = CP_System_GetSeconds();

	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))//클릭시 인트로 스킵
	{
		Introskip++;
	}

	if (Introskip == 0 && introCount <= 3.0f)
	{
		CP_Image_Draw(DigipenLogo, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, introAlpha);

		fadeSlow++;

		if (introAlpha <= 255)
		{
			if (fadeSlow == 1)
				introAlpha++;
			fadeSlow = 0;
		}

	}
	else if (Introskip <= 1 && introCount < 6.0f)
	{


		if (IsAudioPlayed == FALSE) //로고소리 플레이
		{
			introAlpha = 0;
			CP_Sound_PlayAdvanced(LogoSong, 1.5f, 1.0f, 0, 2);
			IsAudioPlayed = TRUE;
		}

		CP_Image_Draw(LogoImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, introAlpha);

		fadeSlow++;

		if (introAlpha <= 255)
		{
			if (fadeSlow == 1)
			{
				introAlpha++;
				fadeSlow = 0;
			}
		}

	}
	else
	{
		CP_Engine_SetNextGameState(MainTitleInit, MainTitleUpdate, MainTitleExit);
	}
}

void IntroExit(void)
{
	CP_Image_Free(&LogoImage);
	CP_Image_Free(&DigipenLogo);

	CP_Sound_Free(&LogoSong);
}