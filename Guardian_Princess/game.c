#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <stdio.h>
#include "game.h"

#define PLAYER_SPEED 400
#define MAX_UNIT 10
#define NUM_ENEMY_TYPES 2

//TODO: unit 구조체 만들기 

extern CP_Image cursorImage;
CP_BOOL cursor;
CP_Vector heroPosition;

CP_BOOL buttonClicked;
CP_Color red;
CP_Color green;
CP_Color blue;
CP_Color white;
static float dt;

Ally ally[MAX_UNIT];
AllySpawner allySpawner[MAX_UNIT];
Enemy enemy[MAX_UNIT];
EnemySpawner enemySpawner[NUM_ENEMY_TYPES];

void initUnit(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		ally[i].position = CP_Vector_Set(0, 0);
		ally[i].collider.radius = 0;
		ally[i].speed = 400;

		enemy[i].position = CP_Vector_Set(0, 0);
		enemy[i].collider.radius = 0;
		enemy[i].speed = 400;
		enemy[i].type = MELEE;
	}

	for (int i = 0; i < NUM_ENEMY_TYPES; i++)
	{
		allySpawner[i].timer = 0;
		enemySpawner[i].timer = 0;
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

	ally[idx].alived = TRUE;
	idx++;
}

void SummonEnemyUnit(EnemyType type)
{
	static int idx = 0;

	printf("index: %d\n", idx);

	if (idx >= MAX_UNIT)
	{
		//printf("Can't summon enemy unit!!!\n");
		return;
	}
	
	enemy[idx].alived = TRUE;
	enemy[idx].type = type;

	idx++; 
}

//TODO: 죽으면 spawnTime = 0으로

void DrawAllyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived)
		{
			CP_Settings_Fill(blue);
			CP_Graphics_DrawCircle(ally[i].position.x, ally[i].position.y, 30);

			ally[i].collider.position = CP_Vector_Set(ally[i].position.x, ally[i].position.y);
			ally[i].collider.radius = 30;
			ally[i].position.x += ally[i].speed * dt;

		}
	}
}

void DrawEnemyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (enemy[i].alived)
		{
			if (enemy[i].type == MELEE)
			{
				CP_Settings_Fill(red);
			}
			else if (enemy[i].type == RANGED)
			{
				CP_Settings_Fill(white);
			}

			CP_Graphics_DrawCircle(enemy[i].position.x, enemy[i].position.y, 30);

			enemy[i].collider.position = CP_Vector_Set(enemy[i].position.x, enemy[i].position.y);
			enemy[i].collider.radius = 30;
			enemy[i].position.x -= enemy[i].speed * dt;
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
		ally[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
		enemy[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
	}

	CP_Settings_TextSize(40.0f);
}

void GameUpdate(void)
{
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
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

	if(timeElapsed(&enemySpawner[0], 1.0f, MELEE))
		SummonEnemyUnit(MELEE);

	if (timeElapsed(&enemySpawner[1], 3.0f, RANGED))
		SummonEnemyUnit(RANGED);

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


	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (circleToCircle(ally[0].collider, enemy[i].collider))
		{
			ally[0].speed = 0;
			enemy[i].speed = 0;
		}
	}
	
	
	CP_Image_Draw(cursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	DrawAllyUnits();
	DrawEnemyUnits();
}

void GameExit(void)
{

}