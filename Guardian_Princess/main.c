#include "cprocessing.h"
#include "SCENE_Intro.h" // ��Ʈ�� 
//---------------------------------------------------;

int main(void)
{
	CP_Engine_SetNextGameState(IntroInit, IntroUpdate, IntroExit);
	CP_System_SetWindowSize(1280, 720); //fhd ������ ȭ��
	CP_Engine_Run();

	return 0;
}