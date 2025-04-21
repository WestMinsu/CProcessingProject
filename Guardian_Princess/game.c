#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
//-------------------------------
#include "SCENE_MainMenu.h"
#include "utils.h"
#include "game.h"
#include "asset_loading.h"
#include "Hero.h"
#include "ally.h"
#include "enemy.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include "enemybase.h"
#include "FUNC_Button.h"

//에셋 목록-----------------------------------------------------------------------------
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image battle_background;
//-----------------------------------------------------------------------------
#define MAX_UNIT 10
#define NUM_ENEMY_TYPES 2
#define UNIT_SPEED 200

CP_Color red;
CP_Color green;
CP_Color blue;
CP_Color white;

Hero hero;
Ally ally[MAX_UNIT];
AllySpawner allySpawner[MAX_UNIT];
Enemy enemy[MAX_UNIT];
EnemySpawner enemySpawner[NUM_ENEMY_TYPES];
AllyResource allyResource;
EnemyBase enemyBase;

//--------------------

void initHero(void)
{
	hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
	hero.collider.radius = 30;
	hero.moveSpeed = HERO_SPEED;

	hero.currentHP = 1000;
	hero.attackDamage = 1;
	hero.attackSpeed = 1;
	hero.attackRange.position = hero.position;
	hero.attackRange.radius = 30;
}

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



void GameInit(void)
{
	//에셋 로딩 ----------------------------------------------------------
	melee_button_image = CP_Image_Load("Assets/In_game/melee.png");
	ranged_button_image = CP_Image_Load("Assets/In_game/ranged.png");
	battle_background = CP_Image_Load("Assets/In_game/battle_background.png");

	InitEnemyBase();
	InitHero();
	initUnit();

	allyResource.money = 300;

	red = CP_Color_CreateHex(0xFF0000FF);
	green = CP_Color_CreateHex(0x00FF00FF);
	blue = CP_Color_CreateHex(0x0000FFFF);
	white = CP_Color_CreateHex(0xFFFFFFFF);
	pink = CP_Color_CreateHex(0xF08080FF);
}

void GameUpdate(void)
{

	// 이미지 드로우--------------------------------------------------------------------------------------

	CP_Image_Draw(battle_background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
	int melee_input = Button_Draw_Square(melee_button_image, CP_System_GetWindowWidth()/4.0f*1, CP_System_GetWindowHeight()/4.0f * 3.0f, CP_System_GetWindowWidth()/8.0f, CP_System_GetWindowHeight() /4.0f, 255);
	int range_input = Button_Draw_Square(ranged_button_image, CP_System_GetWindowWidth()/4.0f*3, CP_System_GetWindowHeight()/4.0f * 3.0f, CP_System_GetWindowWidth() /8.0f, CP_System_GetWindowHeight() /4.0f,255);
	CP_Image_Draw(Cursor_Image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255);
	DrawHero();
	DrawAllyUnits();
	DrawEnemyUnits();

	
	//아군 유닛 소환 ----------------------------------------------------------------------------------------------------------------

	if (melee_input == 0)
	{
		SummonAllyUnit(MELEE);
	}

	if (timeElapsed(enemySpawner, 1.0f, MELEE))
	{
		SummonEnemyUnit(MELEE);
	}

	if (timeElapsed(enemySpawner, 3.0f, MELEE))
	{
		SummonEnemyUnit(MELEE);
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------

	if (range_input == 0)
	{
		SummonAllyUnit(RANGED);
	}

	if (timeElapsed(enemySpawner, 1.0f, RANGED))
	{
		SummonEnemyUnit(RANGED);
	}

	if (timeElapsed(enemySpawner, 3.0f, RANGED))
	{
		SummonEnemyUnit(RANGED);
	}

	//--------------------------------------------------------------------------------------

	float dt = CP_System_GetDt(); //프레임 받기

	if (CP_Input_KeyDown(KEY_Q)) // 매인메뉴 나가는 버튼
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}


	CP_BOOL isFightWithEnemy = FALSE;
	CP_BOOL isFightWithAlly = FALSE;


	// 영웅 전투 -------------------------

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (circleToCircle(hero.attackRange, enemy[i].collider))
		{


			printf("hit hero!!\n");
			enemy[i].currentHP -= hero.attackDamage;
			if (enemy[i].currentHP <= 0)

			enemy[i].currentHP -= hero.attackDamage;
			if (enemy[i].currentHP <= 0)
			{
				enemy[i].alived = FALSE;	
				enemy[i].collider.radius = 0;
				enemy[i].attackRange.radius = 0;
			}
		}

		// 원거리 전투 ------------------

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

	// 유닛 전투
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


	UpdateHero(dt);
	SummonEnemyBase();
	DrawEnemyBase();
	UpdateAllyUnits(dt);
	UpdateEnemyUnits(dt);


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
	
}