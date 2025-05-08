#include <stdio.h>
#include "cprocessing.h"
#include "SCENE_StageEnd.h"
#include "SCENE_MainMenu.h"

#include "game.h"
#include "FUNC_BUTTON.h"
#include "asset_loading.h"
//------------------------------------------------------------------------------------------------

CP_Image Gameover_image;
CP_Image GameVictory_image;
CP_Image goMainButtonImage;
CP_Image ReplayButtonImage;

CP_Sound GameWin;
CP_Sound GameLose;
//------------------------------------------------------------------------------------------------
int BGMPlay = 1;


void StageEndInit(void)
{

	//---------에셋 로딩 -----------------------
	Gameover_image = CP_Image_Load("Assets/stageEnd/gameOverImage.png");
	GameVictory_image = CP_Image_Load("Assets/stageEnd/gameVictoryImage.png");
	goMainButtonImage = CP_Image_Load("Assets/stageEnd/goMain.png");
	ReplayButtonImage = CP_Image_Load("Assets/stageEnd/replay.png");

	GameLose = CP_Sound_Load("Assets/stageEnd/gameLoseBGM.mp3");
	GameWin = CP_Sound_Load("Assets/stageEnd/gameWinBGM.mp3");
}


void StageEndWInUpdate(void)
{
	//음악 재생 변수
	int goMainInput = SquareButtonClicked(goMainButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	int replayInput = SquareButtonClicked(ReplayButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);

	// 음악 재생
	if (BGMPlay == 1)
	{
		CP_Sound_PlayAdvanced(GameWin, 1.0f, 1.0f, 1, BGM);
		BGMPlay = 0;
	}
	//
	if (goMainInput == 0)
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);

	}
	if (replayInput == 0)
	{
		CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
	}

	// 이미지 드로우
	CP_Image_Draw(GameVictory_image, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255); 
	CP_Image_Draw(goMainButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(ReplayButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255); //커서 이미지

}

void StageEndLoseUpdate(void)
{

	//음악 재생 변수


	// 이미지 드로우
	int goMainInput = SquareButtonClicked(goMainButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	int replayInput = SquareButtonClicked(ReplayButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);


	// 음악 재생
	if (BGMPlay == 1)
	{
		CP_Sound_PlayAdvanced(GameLose, 1.0f, 1.0f, 1, BGM);
		BGMPlay = 0;
	}
	//
	if (goMainInput == 0)
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);

	}
	if (replayInput == 0)
	{
		CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
	}

	CP_Image_Draw(Gameover_image, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
	CP_Image_Draw(goMainButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(ReplayButtonImage, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowWidth() / 8.0f, 255);
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255); //커서 이미지
}


void StageEndExit(void)
{
	CP_Image_Free(&GameVictory_image);
	CP_Image_Free(&goMainButtonImage);
	CP_Image_Free(&ReplayButtonImage);
	CP_Image_Free(&Gameover_image);

	CP_Sound_Free(&GameLose);
	CP_Sound_Free(&GameWin);


}
