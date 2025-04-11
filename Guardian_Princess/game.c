#define _USE_MATH_DEFINES
#include <math.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <stdio.h>
#include "game.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400
#define MAX_UNIT 10

CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
float textSize;

extern CP_Image Cursor_image;
extern CP_BOOL cursor;
CP_Vector hero_position;
CP_Vector unit_position[MAX_UNIT];
CP_BOOL unit_alived[MAX_UNIT];
CP_BOOL button_clicked;
CP_Color red;
CP_Color green;
CP_Color blue;
CP_Color white;
float dt;

void Summon_Unit(void)
{

	static int idx = 0;
	if (button_clicked)
	{
		printf("index: %d\n", idx);

		if (idx >= MAX_UNIT)
		{
			printf("Can't summon unit!!!\n");
			button_clicked = FALSE;
			return;
		}

		unit_alived[idx] = TRUE;
		idx++;
		button_clicked = FALSE;
	}

}

void Draw_Unit(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (unit_alived[i])
		{
			CP_Settings_Fill(blue);
			CP_Graphics_DrawCircle(unit_position[i].x, unit_position[i].y, 30);
			unit_position[i].x += PLAYER_SPEED * dt;
		}
	}

}

void Game_Init(void)
{
	CP_System_ShowCursor(cursor);
	hero_position = CP_Vector_Set(100, 100);

	for (int i = 0; i < MAX_UNIT; i++)
	{
		unit_position[i] = CP_Vector_Set(100, 100);
	}

	textSize = 40.0f;
	CP_Settings_TextSize(textSize);

}

void Game_Update(void)
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
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Font_DrawText("Summon", summonButton_x, summonButton_y);


	CP_Settings_Fill(red);
	CP_Graphics_DrawCircle(hero_position.x, hero_position.y, 30);

	if (IsAreaClicked(summonButton_x, summonButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		button_clicked = TRUE;
	}

	Summon_Unit();
	Draw_Unit();

	if (CP_Input_KeyDown(KEY_A))
	{
		hero_position.x -= PLAYER_SPEED * dt;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		hero_position.x += PLAYER_SPEED * dt;
	}


	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;
	CP_Image_Draw(Cursor_image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);

}

void Game_Exit(void)
{

}