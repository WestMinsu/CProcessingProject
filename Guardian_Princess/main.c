#include "cprocessing.h"

//------------------��� ���� ���� �ڵ�--------------------

#include "SCENE_MainMenu.h" //���θ޴� ��ȣ �ۿ�
#include "SCENE_Intro.h" // ��Ʈ�� ����

//---------------------------------------------------;

int main(void)
{
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run();
	
	return 0;
}

