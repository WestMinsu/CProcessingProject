#include "cprocessing.h"
#include "SCENE_MainMenu.h"
#include "utils.h"
#include "FUNC_Animation_Motion.h"
#include "game.h"
#include "asset_loading.h"
#include "hero.h"
#include "ally.h"
#include "enemy.h"
#include "constants.h"
#include "colors.h"
#include "globals.h"
#include <stdio.h>
#include "FUNC_Button.h"

//에셋 목록-----------------------------------------------------------------------------
CP_Image melee_button_image;
CP_Image ranged_button_image;
//-----------------------------------------------------------------------------
Hero hero;
Ally ally[MAX_UNIT];
AllySpawner allySpawner[MAX_UNIT];
Enemy enemy[MAX_UNIT];
EnemySpawner enemySpawner[NUM_ENEMY_TYPES];

void initUnit(void)
{
	Sound_load();
	Image_load();
	Font_load();


	for (int i = 0; i < MAX_UNIT; i++)
	{
		ally[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
		ally[i].collider.radius = 0;
		ally[i].moveSpeed = UNIT_SPEED;
		ally[i].type = MELEE;

		ally[i].hp = 100;
		ally[i].attackDamage = 1; 
		ally[i].attackSpeed = 1;
		ally[i].attackRange.position = ally[i].position;
		ally[i].attackRange.radius = 0;

		enemy[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
		enemy[i].collider.radius = 0;
		enemy[i].moveSpeed = UNIT_SPEED;
		enemy[i].type = MELEE;

		enemy[i].hp = 100;
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

	//----------------------------------------------------------------


	initHero();
	initUnit();

	red = CP_Color_CreateHex(0xFF0000FF);
	green = CP_Color_CreateHex(0x00FF00FF);
	blue = CP_Color_CreateHex(0x0000FFFF);
	white = CP_Color_CreateHex(0xFFFFFFFF);

	CP_Settings_TextSize(40.0f);
}

void GameUpdate(void)
{

	dt = CP_System_GetDt(); //프레임 받기

	if (CP_Input_KeyDown(KEY_Q)) // 매인메뉴 나가는 버튼
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}


	// 버튼 함수 ------------------------------------------

	int melee_input = Button_Draw_Square(melee_button_image, CP_System_GetWindowWidth()/2.0f, CP_System_GetWindowHeight()/4.0f * 3.0f, CP_System_GetWindowWidth()/4.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	int range_input = Button_Draw_Square(ranged_button_image, CP_System_GetWindowWidth()/2.0f + 100, CP_System_GetWindowHeight()/4.0f * 3.0f, CP_System_GetWindowWidth() / 4.0f, CP_System_GetWindowHeight() / 4.0f,255);

	//아군 유닛 소환 ----------------------------
	if (melee_input == 0)
	{
		SummonAllyUnit(MELEE);
	}
	
	if (range_input == 0)
	{
		SummonAllyUnit(RANGED);
	}

	//적 유닛 소환 --------------------------

	if (timeElapsed(enemySpawner, 1.0f, MELEE))
	{
		SummonEnemyUnit(MELEE);
	}

	if (timeElapsed(enemySpawner, 3.0f, RANGED))
	{
		SummonEnemyUnit(RANGED);
	}

	//------------------------------

	CP_BOOL isFightWithEnemy = FALSE;
	CP_BOOL isFightWithAlly = FALSE;

	// 영웅 전투 -------------------------

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (circleToCircle(hero.attackRange, enemy[i].collider))
		{
			printf("hit hero!!\n");
			enemy[i].hp -= hero.attackDamage;
			if (enemy[i].hp <= 0)
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
			printf("damaged hero!\n");
			hero.hp -= enemy[i].attackDamage;

			if (hero.hp <= 0)
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

				enemy[j].hp -= ally[i].attackDamage;
				if (enemy[j].hp <= 0)
				{
					enemy[j].alived = FALSE;
					enemy[j].collider.radius = 0;
					enemy[j].attackRange.radius = 0;
				}	
			}
			if (circleToCircle(enemy[j].attackRange, ally[i].collider))
			{
				isFightWithAlly = TRUE;
				enemy[j].moveSpeed = 0;

				ally[i].hp -= enemy[j].attackDamage;
				if (ally[i].hp <= 0)
				{
					ally[i].alived = FALSE;
					ally[i].collider.radius = 0;
					ally[i].attackRange.radius = 0;
				}
			}
			if (!isFightWithEnemy)
			{
				ally[i].moveSpeed = UNIT_SPEED;
				//isFightWithEnemy = FALSE;
			}
			if (!isFightWithAlly)
			{
				enemy[j].moveSpeed = UNIT_SPEED;
				//isFightWithAlly = FALSE;
			}
		}

	}
	



	CP_Image_Draw(Cursor_Image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255);


	DrawHero();
	DrawAllyUnits();
	DrawEnemyUnits();
}


void GameExit(void)
{

}