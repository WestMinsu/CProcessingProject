#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_Intro.h"
#include "SCENE_MainMenu.h"
#include "SCENE_MainTitle.h"
//���� �ε�------------------------------------------------------------------------------------------------
CP_Sound LogoSong;
CP_Image DigipenLogo;
CP_Image LogoImage;
//--���̵� ��, �ƿ� ����------

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

	LogoSong = CP_Sound_Load("Assets/Intro/frostbyte_logo.mp3");
	LogoImage = CP_Image_Load("Assets/Intro/logo_image.png");
	DigipenLogo = CP_Image_Load("Assets/Intro/Digipen_logo.png");
}

void IntroUpdate(void)
{

	static int introAlpha = 0; // ȭ�� Ʈ������ (���İ� ����)
	static int fadeSlow = 0; //ȭ�� Ʈ������ �ӵ� ���� 
	static int IsAudioPlayed = FALSE; // ����� �ѹ��� ��� 
	static int Introskip = 0; //Ŭ���� ��Ʈ�� ��ŵ Ȯ�� ����


	float introCount = CP_System_GetSeconds();

	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))//Ŭ���� ��Ʈ�� ��ŵ
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


		if (IsAudioPlayed == FALSE) //�ΰ�Ҹ� �÷���
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