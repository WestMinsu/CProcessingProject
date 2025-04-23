#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_Intro.h"
#include "SCENE_MainMenu.h"
//���� �ε�------------------------------------------------------------------------------------------------
CP_Sound LogoSong;
CP_Image DigipenLogo;
CP_Image LogoImage;
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
	CP_Engine_SetPreUpdateFunction(GamePreUpdate); //���� ������Ʈ ����
	//���� �ʱ� �ý��� ����--------------------------------
	CP_System_SetWindowTitle("Guardian Princess"); //���α׷� â �̸� 
	CP_Settings_ImageMode(CP_POSITION_CENTER); //�̹��� ���� ����� ����.
	CP_Color Default_BG = CP_Color_Create(0, 0, 0, 255);
	CP_Graphics_ClearBackground(Default_BG); //�⺻ ��� ����
	//���� �ε�--------------------------------

	LogoSong = CP_Sound_Load("Assets/intro/frostbyte_logo.mp3");
	LogoImage = CP_Image_Load("Assets/intro/logo_image.png");
	DigipenLogo = CP_Image_Load("Assets/intro/Digipen_logo.png");
}

void IntroUpdate(void)
{

	static int IsAudioPlayed = FALSE;
	static int skip = 0;
	float introCount = CP_System_GetSeconds();

	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
	{
		skip++;
	}


	if (skip == 0 && introCount <= 3.0f)
	{
		CP_Image_Draw(DigipenLogo, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);

	}
	else if (skip <= 1 && introCount < 6.0f)
	{
		CP_Image_Draw(LogoImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);

		if (IsAudioPlayed == FALSE)
		{
			CP_Sound_PlayAdvanced(LogoSong, 1.5f, 1.0f, 0, 2);
			IsAudioPlayed = TRUE;
		}
	}
	else
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}
}

void IntroExit(void)
{
	CP_Image_Free(&LogoImage);
	CP_Image_Free(&DigipenLogo);

	CP_Sound_Free(&LogoSong);
}