#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_Intro.h"
#include "SCENE_MainMenu.h"
//���� �ε�------------------------------------------------------------------------------------------------
CP_Sound Logo_song;
CP_Image digipen_logo;
CP_Image Logo_image;

//--------------

int should_play = 1;

void GAME_PREUPDATE(void)
{
	Image_load();
	Sound_load();
	Font_load();
	CP_System_ShowCursor(FALSE);
}

void Intro_Init(void)
{
	CP_Engine_SetPreUpdateFunction(GAME_PREUPDATE); //���� ������Ʈ ����
	//���� �ʱ� �ý��� ����--------------------------------
	CP_System_SetWindowTitle("Guardian Princess"); //���α׷� â �̸� 
	CP_Settings_ImageMode(CP_POSITION_CENTER); //�̹��� ���� ����� ����.
	CP_Color Default_BG = CP_Color_Create(0, 0, 0, 255); 
	CP_Graphics_ClearBackground(Default_BG); //�⺻ ��� ����
	//���� �ε�--------------------------------

	Logo_song = CP_Sound_Load("Assets/intro/frostbyte_logo.mp3");
	Logo_image = CP_Image_Load("Assets/intro/logo_image.png");
	digipen_logo = CP_Image_Load("Assets/intro/Digipen_logo.png");
}

void Intro_Update(void)
{
	float intro_count = CP_System_GetSeconds();
	
	if (intro_count <= 3.0f)
	{
		CP_Image_Draw(digipen_logo, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
	}
	else if (intro_count > 3.0f && intro_count <6.0f)
	{
		CP_Image_Draw(Logo_image, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
		if (should_play)
		{
			CP_Sound_PlayAdvanced(Logo_song, 1.5f, 1.0f,0,BGM);
			should_play = 0;
		}

	}
	else if(intro_count > 6.0f)
	{ 
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}	
	else
	{
	}
}

void Intro_Exit(void)
{
	CP_Image_Free(&Logo_image);
	CP_Image_Free(&digipen_logo);

	CP_Sound_Free(&Logo_song);
}