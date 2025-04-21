#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_Intro.h"
#include "SCENE_MainMenu.h"
//���� �ε�------------------------------------------------------------------------------------------------


CP_Image Intro_digipen; //������ �ΰ�
CP_Image Intro_teamlogo;//�� �ΰ� ���
CP_Image Intro_bic;//bic �ΰ� ���

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

	Intro_bic = CP_Image_Load("Assets/intro_assets/bic_logo.png");
	Intro_digipen = CP_Image_Load("Assets/intro_assets/digipen_logo.png");
	Intro_teamlogo = CP_Image_Load("Assets/intro_assets/frostbyte_logo.png");
}

void Intro_Update(void)
{
	CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
}

void Intro_Exit(void)
{



}