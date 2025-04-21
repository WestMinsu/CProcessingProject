#include "cprocessing.h"
#include "asset_loading.h"
#include "SCENE_Intro.h"
#include "SCENE_MainMenu.h"
//에셋 로딩------------------------------------------------------------------------------------------------


CP_Image Intro_digipen; //디지펜 로고
CP_Image Intro_teamlogo;//팀 로고 출력
CP_Image Intro_bic;//bic 로고 출력

void GAME_PREUPDATE(void)
{
	Image_load();
	Sound_load();
	Font_load();
	CP_System_ShowCursor(FALSE);
}

void Intro_Init(void)
{
	CP_Engine_SetPreUpdateFunction(GAME_PREUPDATE); //프리 스테이트 설정

	//게임 초기 시스템 설정--------------------------------
	CP_System_SetWindowTitle("Guardian Princess"); //프로그램 창 이름 
	CP_Settings_ImageMode(CP_POSITION_CENTER); //이미지 중점 가운데로 설정.

	CP_Color Default_BG = CP_Color_Create(0, 0, 0, 255); 
	CP_Graphics_ClearBackground(Default_BG); //기본 배경 설정
	//에셋 로딩--------------------------------

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