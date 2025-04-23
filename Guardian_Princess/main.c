#include "cprocessing.h"
#include "SCENE_Intro.h" // 인트로 
//---------------------------------------------------;

int main(void)
{
	CP_Engine_SetNextGameState(IntroInit, IntroUpdate, IntroExit);
	CP_System_SetWindowSize(1920, 1080); //fhd 사이즈 화면
	CP_Engine_Run();
	
	return 0;
}