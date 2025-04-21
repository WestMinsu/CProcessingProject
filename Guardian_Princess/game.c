#include "cprocessing.h"
#include "SCENE_MainMenu.h"
#include "utils.h"
#include "game.h"
#include "asset_loading.h"
#include "hero.h"
#include "ally.h"
#include "enemy.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include "enemybase.h"
#include <stdio.h>





#include <stdlib.h>

Hero hero;
Ally ally[MAX_UNIT];
AllySpawner allySpawner[MAX_UNIT];
Enemy enemy[MAX_UNIT];
EnemySpawner enemySpawner[NUM_ENEMY_TYPES];
AllyResource allyResource;
EnemyBase enemyBase;

void initUnit(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		ally[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
		ally[i].collider.radius = 0;
		ally[i].moveSpeed = UNIT_SPEED;
		ally[i].type = MELEE;

		ally[i].currentHP = 100;
		ally[i].attackDamage = 1; 
		ally[i].attackSpeed = 1;
		ally[i].attackRange.position = ally[i].position;
		ally[i].attackRange.radius = 0;
		ally[i].price = 30;

		enemy[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
		enemy[i].collider.radius = 0;
		enemy[i].moveSpeed = UNIT_SPEED;
		enemy[i].type = MELEE;

		enemy[i].currentHP = 100;
		enemy[i].attackDamage = 1;
		enemy[i].attackSpeed = 1;
		enemy[i].attackRange.position = enemy[i].position;
		enemy[i].attackRange.radius = 0;
	}

	for (int i = 0; i < NUM_ENEMY_TYPES; i++)
	{
		allySpawner[i].timer = 0;
		enemySpawner[i].timer = 0;
	}
}

//TODO: 죽으면 spawnTime = 0으로

void GameInit(void)
{
	CP_System_ShowCursor(FALSE);

	InitEnemyBase();
	InitHero();
	initUnit();

	allyResource.money = 300;

	red = CP_Color_CreateHex(0xFF0000FF);
	green = CP_Color_CreateHex(0x00FF00FF);
	blue = CP_Color_CreateHex(0x0000FFFF);
	white = CP_Color_CreateHex(0xFFFFFFFF);
	pink = CP_Color_CreateHex(0xF08080FF);

	CP_Settings_TextSize(40.0f);
}

void GameUpdate(void)
{
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	float dt = CP_System_GetDt();

	// 버튼 위치
	float summonMeleeButton_x = CP_System_GetWindowWidth() / 2.0f - 250;
	float summonMeleeButton_y = CP_System_GetWindowHeight() / 4.0f * 3.0f;
	float buttonWidth = CP_System_GetWindowWidth() / 4.0f;
	float buttonHeight = CP_System_GetWindowHeight() / 4.0f;

	// 버튼(직사각형 모양) 그리기
	CP_Settings_Fill(white);
	CP_Graphics_DrawRect(summonMeleeButton_x, summonMeleeButton_y, buttonWidth, buttonHeight);
	
	// 글씨 쓰기
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Font_DrawText("Melee", summonMeleeButton_x, summonMeleeButton_y);

	float summonRangedButton_x = CP_System_GetWindowWidth() / 2.0f + 250;
	float summonRangedButton_y = CP_System_GetWindowHeight() / 4.0f * 3.0f;

	// 버튼(직사각형 모양) 그리기
	CP_Settings_Fill(white);
	CP_Graphics_DrawRect(summonRangedButton_x, summonRangedButton_y, buttonWidth, buttonHeight);

	// 글씨 쓰기
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Font_DrawText("Ranged", summonRangedButton_x, summonRangedButton_y);

	if (IsAreaClicked(summonMeleeButton_x, summonMeleeButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		SummonAllyUnit(MELEE);
	}

	if (IsAreaClicked(summonRangedButton_x, summonRangedButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		SummonAllyUnit(RANGED);
	}

	if (timeElapsed(enemySpawner, 1.0f, MELEE))
	{
		SummonEnemyUnit(MELEE);
	}

	if (timeElapsed(enemySpawner, 3.0f, RANGED))
	{
		SummonEnemyUnit(RANGED);
	}

	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;

	CP_BOOL isFightWithEnemy = FALSE;
	CP_BOOL isFightWithAlly = FALSE;

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (circleToCircle(hero.attackRange, enemy[i].collider))
		{
			enemy[i].currentHP -= hero.attackDamage;
			if (enemy[i].currentHP <= 0)
			{
				enemy[i].alived = FALSE;	
				enemy[i].collider.radius = 0;
				enemy[i].attackRange.radius = 0;
			}
		}

		if (circleToCircle(enemy[i].attackRange, hero.collider))
		{
			isFightWithAlly = TRUE;
			enemy[i].moveSpeed = 0;

			hero.currentHP -= enemy[i].attackDamage;
			if (hero.currentHP <= 0)
			{
				printf("hero dead\n");
				hero.moveSpeed = 0;
				printf("hero movespeed: %d", hero.moveSpeed);
				hero.collider.radius = 0;
				hero.attackRange.radius = 0;
			}
		}
	}

	for (int i=0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (circleToCircle(ally[i].attackRange, enemy[j].collider))
			{
				isFightWithEnemy = TRUE;
				ally[i].moveSpeed = 0;

				enemy[j].currentHP -= ally[i].attackDamage;
				if (enemy[j].currentHP <= 0)
				{
					enemy[j].alived = FALSE;
					enemy[j].collider.radius = 0;
					enemy[j].attackRange.radius = 0;
				}	
			}

			if (!isFightWithEnemy)
			{
				ally[i].moveSpeed = UNIT_SPEED;
				isFightWithEnemy = FALSE;
			}

		}
	}
	
	for (int i = 0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (circleToCircle(enemy[j].attackRange, ally[i].collider))
			{
				isFightWithAlly = TRUE;
				enemy[j].moveSpeed = 0;

				ally[i].currentHP -= enemy[j].attackDamage;
				if (ally[i].currentHP <= 0)
				{
					ally[i].alived = FALSE;
					ally[i].collider.radius = 0;
					ally[i].attackRange.radius = 0;
				}
			}

			if (!isFightWithAlly)
			{
				enemy[j].moveSpeed = UNIT_SPEED;
				isFightWithAlly = FALSE;
			}
		}
	}

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (circleToCircle(ally[i].attackRange, enemyBase.collider) && !isFightWithEnemy)
		{
			ally[i].moveSpeed = 0;

			enemyBase.currentHP -= ally[i].attackDamage;
			if (enemyBase.currentHP <= 0)
			{
				enemyBase.alived = FALSE;
				enemyBase.collider.radius = 0;
				ally[i].moveSpeed = UNIT_SPEED;
			}
		}
	}

	CP_Image_Draw(Cursor_Image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	UpdateHero(dt);


	SummonEnemyBase();
	DrawEnemyBase();
	UpdateAllyUnits(dt);
	UpdateEnemyUnits(dt);
	DrawHero();
	DrawAllyUnits();
	DrawEnemyUnits();

	char heroHP[50] = { 0 };
	sprintf_s(heroHP, _countof(heroHP), "%d / %d", hero.currentHP, hero.maxHP);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText(heroHP, hero.position.x, hero.position.y - 30);
	
	char enemyBaseHP[50] = { 0 };
	sprintf_s(enemyBaseHP, _countof(enemyBaseHP), "%d / %d", enemyBase.currentHP, enemyBase.maxHP);
	CP_Font_DrawText(enemyBaseHP, enemyBase.position.x, enemyBase.position.y - 30);
}

void GameExit(void)
{
	// TODO: free
	// 
	// 
	// 
	// 
	// 
	// 
}