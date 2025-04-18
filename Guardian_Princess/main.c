#include "cprocessing.h"

//------------------장면 연출 관련 코드--------------------

#include "SCENE_MainMenu.h" //메인메뉴 상호 작용
#include "SCENE_Intro.h" // 인트로 연출

//---------------------------------------------------;

int main(void)
{
	CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run();
	
	return 0;
}