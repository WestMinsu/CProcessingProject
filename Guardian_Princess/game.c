#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <stdio.h>
#include "game.h"

#define PLAYER_SPEED 400
#define MAX_UNIT 10

//TODO: unit 구조체 만들기 

extern CP_Image cursorImage;
CP_BOOL cursor;
CP_Vector heroPosition;
CP_Vector allyUnitPosition[MAX_UNIT];
CP_BOOL allyUnitAlived[MAX_UNIT];
CP_Vector enemyUnitPosition[MAX_UNIT];
CP_BOOL enemyUnitAlived[MAX_UNIT];
CP_BOOL buttonClicked;
CP_Color red;
CP_Color green;
CP_Color blue;
CP_Color white;
static float dt;

struct Circle allyCollider[MAX_UNIT];
struct Circle enemyCollider[MAX_UNIT];
int allyUnitSpeed[MAX_UNIT];
int enemyUnitSpeed[MAX_UNIT];

void initUnit(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		allyCollider[i].position = CP_Vector_Set(0, 0);
		allyCollider[i].radius = 0;
		enemyCollider[i].position = CP_Vector_Set(0, 0);
		enemyCollider[i].radius = 0;
		allyUnitSpeed[i] = 400;
		enemyUnitSpeed[i] = 400;
	}
}

void SummonAllyUnit(void)
{
	static int idx = 0;

	printf("index: %d\n", idx);

	if (idx >= MAX_UNIT)
	{
		printf("Can't summon ally unit!!!\n");
		buttonClicked = FALSE;
		return;
	}

	allyUnitAlived[idx] = TRUE;
	idx++;
}

void SummonEnemyUnit(void)
{
	static int idx = 0;

	//printf("index: %d\n", idx);

	if (idx >= MAX_UNIT)
	{
		//printf("Can't summon enemy unit!!!\n");
		return;
	}

	enemyUnitAlived[idx] = TRUE;
	idx++;

}

void DrawAllyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (allyUnitAlived[i])
		{
			CP_Settings_Fill(blue);
			CP_Graphics_DrawCircle(allyUnitPosition[i].x, allyUnitPosition[i].y, 30);

			allyCollider[i].position = CP_Vector_Set(allyUnitPosition[i].x, allyUnitPosition[i].y);
			allyCollider[i].radius = 30;
			allyUnitPosition[i].x += allyUnitSpeed[i] * dt;

		}
	}

}

void DrawEnemyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (enemyUnitAlived[i])
		{
			CP_Settings_Fill(red);
			CP_Graphics_DrawCircle(enemyUnitPosition[i].x, enemyUnitPosition[i].y, 30);

			enemyCollider[i].position = CP_Vector_Set(enemyUnitPosition[i].x, enemyUnitPosition[i].y);
			enemyCollider[i].radius = 30;
			enemyUnitPosition[i].x -= allyUnitSpeed[i] * dt;

		}
	}
}

void GameInit(void)
{
	CP_System_ShowCursor(cursor);
	heroPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);

	initUnit();

	for (int i = 0; i < MAX_UNIT; i++)
	{
		allyUnitPosition[i] = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
		enemyUnitPosition[i] = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
	}

	CP_Settings_TextSize(40.0f);
}

void GameUpdate(void)
{
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	dt = CP_System_GetDt();

	red = CP_Color_CreateHex(0xFF0000FF);
	green = CP_Color_CreateHex(0x00FF00FF);
	blue = CP_Color_CreateHex(0x0000FFFF);
	white = CP_Color_CreateHex(0xFFFFFFFF);

	float summonButton_x = CP_System_GetWindowWidth() / 2.0f;
	float summonButton_y = CP_System_GetWindowHeight() / 4.0f * 3.0f;
	float buttonWidth = CP_System_GetWindowWidth() / 4.0f;
	float buttonHeight = CP_System_GetWindowHeight() / 4.0f;
	CP_Settings_Fill(white);
	CP_Graphics_DrawRect(summonButton_x, summonButton_y, buttonWidth, buttonHeight);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));

	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);

	CP_Font_DrawText("Summon", summonButton_x, summonButton_y);

	CP_Settings_Fill(green);
	CP_Graphics_DrawCircle(heroPosition.x, heroPosition.y, 30);

	if (IsAreaClicked(summonButton_x, summonButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		buttonClicked = TRUE;
	}

	if (buttonClicked)
	{
		SummonAllyUnit();
		buttonClicked = FALSE;
	}

	if (timeElapsed(1.0f))
	{
		SummonEnemyUnit();

	}

	if (CP_Input_KeyDown(KEY_A))
	{
		heroPosition.x -= PLAYER_SPEED * dt;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		heroPosition.x += PLAYER_SPEED * dt;
	}

	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;


	if (circleToCircle(allyCollider[0], enemyCollider[0]))
	{
		allyUnitSpeed[0] = 0;
		enemyUnitSpeed[0] = 0;
	}

	CP_Image_Draw(cursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	DrawAllyUnits();
	DrawEnemyUnits();
}

void GameExit(void)
{

}