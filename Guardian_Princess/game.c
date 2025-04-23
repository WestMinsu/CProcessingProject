#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "SCENE_MainMenu.h"
#include "utils.h"
#include "game.h"
#include "asset_loading.h"
#include "hero.h"
#include "unit.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include "enemybase.h"

Hero hero;
AllySpawner allySpawner[MAX_UNIT];
EnemySpawner enemySpawner[NUM_ENEMY_TYPES];
Resource allyResource;
Resource enemyResource;
EnemyBase enemyBase;
CP_BOOL isFightWithEnemy[MAX_UNIT];
CP_BOOL isFightWithAlly[MAX_UNIT];
Unit ally[MAX_UNIT];
Unit enemy[MAX_UNIT];

//TODO: 죽으면 spawnTime = 0으로

void GameInit(void)
{
	CP_System_ShowCursor(FALSE);

	InitEnemyBase();
	InitHero();
	InitUnit();

	allyPopulation = 0;
	enemyPopulation = 0;
	
	for (int i = 0; i < MAX_UNIT; i++)
	{
		isFightWithEnemy[i] = FALSE;
		isFightWithAlly[i] = FALSE;
	}

	allyResource.money = 300;
	enemyResource.money = 10000;

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
	SummonEnemyBase();

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
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (!ally[i].alived)
			{
				SummonUnit(ally, WARRIOR);
				break;
			}
		}
	}

	if (IsAreaClicked(summonRangedButton_x, summonRangedButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (!ally[i].alived)
			{
				SummonUnit(ally, ARCHER);
				break;
			}
		}
	}

	if (timeElapsed(enemySpawner, 1.3f, WARRIOR))
	{
		SummonUnit(enemy, WARRIOR);
	}

	if (timeElapsed(enemySpawner, 3.0f, ARCHER))
	{
		SummonUnit(enemy, ARCHER);
	}

	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;


	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (circleToCircle(hero.attackRange, enemy[j].collider))
		{
			enemy[j].currentHP -= hero.attackDamage;
			if (enemy[j].currentHP <= 0)
			{
				enemy[j].alived = FALSE;
				enemy[j].collider.radius = 0;
				enemy[j].attackRange.radius = 0;
			}
		}

		if (circleToCircle(enemy[j].attackRange, hero.collider))
		{
			isFightWithAlly[j] = TRUE;
			enemy[j].moveSpeed = 0;

			hero.currentHP -= enemy[j].attackDamage;
			if (hero.currentHP <= 0)
			{
				printf("hero dead\n");
				hero.moveSpeed = 0;
				hero.collider.radius = 0;
				hero.attackRange.radius = 0;
				isFightWithAlly[j] = FALSE;
				enemy[j].moveSpeed = UNIT_SPEED;
			}
		}
		else
			enemy[j].moveSpeed = UNIT_SPEED;
	}

	//find target
	for (int i = 0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (circleToCircle(ally[i].attackRange, enemy[j].collider))
			{
				if (!isFightWithEnemy[i] || ally[i].targetUnit == NULL)
				{
					ally[i].targetUnit = &enemy[j];
					isFightWithEnemy[i] = TRUE;
				}
				ally[i].moveSpeed = 0;

			}
		}
	}

	//attack target
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].targetUnit != NULL)
		{
			ally[i].targetUnit->currentHP -= ally[i].attackDamage;
			//printf("enemy hp: %d\n", ally[i].targetUnit->currentHP);
			if (ally[i].targetUnit->currentHP <= 0)
			{
				ally[i].targetUnit->position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
				ally[i].targetUnit->alived = FALSE;
				ally[i].targetUnit->collider.radius = 0;
				ally[i].targetUnit->attackRange.radius = 0;

				isFightWithEnemy[i] = FALSE;
				ally[i].targetUnit = NULL;
	/*			if (enemyPopulation > 0)
				{
					enemyPopulation--;
					printf("%d\n", enemyPopulation);
				}*/
			}
		}
		if (!isFightWithEnemy[i])
		{
			ally[i].moveSpeed = UNIT_SPEED;
		}
	}

	//find target
	for (int i = 0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (circleToCircle(enemy[j].attackRange, ally[i].collider))
			{
				if (!isFightWithAlly[j] || enemy[j].targetUnit == NULL)
				{
					enemy[j].targetUnit = &ally[i];
					isFightWithAlly[j] = TRUE;
				}
				enemy[j].moveSpeed = 0;
			}
		}
	}

	//attack target
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].targetUnit != NULL)
		{
			enemy[j].targetUnit->currentHP -= enemy[j].attackDamage;
			//printf("ally hp: %d\n", enemy[j].targetUnit->currentHP);
			if (enemy[j].targetUnit->currentHP <= 0)
			{
				enemy[j].targetUnit->position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
				enemy[j].targetUnit->alived = FALSE;
				enemy[j].targetUnit->collider.radius = 0;
				enemy[j].targetUnit->attackRange.radius = 0;

				isFightWithAlly[j] = FALSE;
				enemy[j].targetUnit = NULL;
				if (allyPopulation > 0)
				{
					allyPopulation--;
					printf("%d\n", allyPopulation);
				}
			}
		}
		if (!isFightWithAlly[j])
		{
			enemy[j].moveSpeed = UNIT_SPEED;
		}
	}

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (circleToCircle(ally[i].attackRange, enemyBase.collider) && !isFightWithEnemy[i])
		{
			ally[i].moveSpeed = 0;

			enemyBase.currentHP -= ally[i].attackDamage;
			if (enemyBase.currentHP <= 0)
			{
				//TODO: stage clear
			}
		}
	}

	UpdateHero(dt);
	UpdateUnits(dt);

	CP_Image_Draw(cursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	DrawEnemyBase();
	DrawHero();
	DrawUnits(ally);
	DrawUnits(enemy);

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