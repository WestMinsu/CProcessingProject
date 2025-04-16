#include "cprocessing.h"
#include "mainmenu.h"
#include "asset_loading.h"
#include "utils.h"
int main(void)
{
	CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run();
	return 0;
}
