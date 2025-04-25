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
#include "FUNC_Button.h"
#include "FUNC_Animation_Motion.h"
#include "SCENE_StageEnd.h"


Hero hero;
UnitSpawner allySpawner[NUM_UNIT_TYPES];
UnitSpawner enemySpawner[NUM_UNIT_TYPES];
Resource allyResource;
Resource enemyResource;
EnemyBase enemyBase;
CP_BOOL isFightWithEnemy[MAX_UNIT];
CP_BOOL isFightWithAlly[MAX_UNIT];
Unit ally[MAX_UNIT];
Unit enemy[MAX_UNIT];
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image battle_background;
AttackTimer unitAttackTimer[MAX_UNIT];
AttackTimer heroAttackTimer;
CP_BOOL isClicked[NUM_UNIT_TYPES];

//-------------------------------------------------------
CP_Image* heroAttack;
CP_Image* heroDead;
CP_Image* heroHurt;
CP_Image* heroWait;
CP_Image* heroWalk;

CP_Image* unitTest;
CP_Image* unitTest2;
//--------------------------------------------------------

extern CP_Vector allyPosition;
extern CP_Vector enemyPosition;

//TODO: 죽으면 spawnTime = 0으로

void GameInit(void)
{
	CP_System_ShowCursor(FALSE);

	//에셋 로딩 ----------------------------------
	melee_button_image = CP_Image_Load("Assets/In_game/melee.png");
	ranged_button_image = CP_Image_Load("Assets/In_game/ranged.png");
	battle_background = CP_Image_Load("Assets/In_game/battle_background.png");

	heroAttack = Animation_ImageLoader("hero_attack", 5);
	heroDead = Animation_ImageLoader("hero_dead", 4);
	heroHurt = Animation_ImageLoader("hero_hurt", 1);
	heroWait = Animation_ImageLoader("hero_wait", 5);
	heroWalk = Animation_ImageLoader("hero_walk", 7);

	unitTest = Animation_ImageLoader("unit_test", 19);
	unitTest2 = Animation_ImageLoader("unit_test2", 14);

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

	allyResource.money = 50;
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

	//CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	SummonEnemyBase();

	// TODO: Button_Draw_Square 함수 Draw만 하게 수정하기(값 반환x), Draw함수는 함수 뒷부분에서 호출
	CP_Image_Draw(battle_background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
	int melee_input = Button_Draw_Square(melee_button_image, CP_System_GetWindowWidth() / 4.0f * 1, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	int range_input = Button_Draw_Square(ranged_button_image, CP_System_GetWindowWidth() / 4.0f * 3, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), CP_System_GetWindowWidth() / 25.0f, CP_System_GetWindowHeight() / 20.0f, 255);

	float dt = CP_System_GetDt();

	if (melee_input == 0)
	{
		isClicked[0] = TRUE;
	}

	if (isClicked[0])	
	{
		if (SpawnTimeElapsed(allySpawner, 1.3f, WARRIOR))
		{
			SummonUnit(ally, WARRIOR);
			isClicked[0] = FALSE;
		}
	}

	if (range_input == 0)
	{
		isClicked[1] = TRUE;
	}

	if (isClicked[1])
	{
		if (SpawnTimeElapsed(allySpawner, 3.0f, ARCHER))
		{
			SummonUnit(ally, ARCHER);
			isClicked[1] = FALSE;
		}
	}
	
	if (SpawnTimeElapsed(enemySpawner, 1.3f, WARRIOR))
	{
		SummonUnit(enemy, WARRIOR);
	}

	if (SpawnTimeElapsed(enemySpawner, 3.0f, ARCHER))
	{
		SummonUnit(enemy, ARCHER);
	}

	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;

	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (circleToCircle(hero.attackRange, enemy[j].collider))
		{
			if (hero.targetUnit == NULL)
			{
				hero.targetUnit = &enemy[j];
			}
		}
	}

	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (hero.targetUnit != NULL)
		{
			if (heroAttackTimeElapsed(hero.attackCoolDown))
			{
				hero.targetUnit->currentHP -= hero.attackDamage;
				printf("enemy HP: %d\n", hero.targetUnit->currentHP);
				if (hero.targetUnit->currentHP <= 0)
				{
					hero.targetUnit->position = enemyPosition;
					hero.targetUnit->alived = FALSE;
					hero.targetUnit->collider.radius = 0;
					hero.targetUnit->attackRange.radius = 0;
					hero.targetUnit = NULL;
					if (enemyPopulation > 0)
					{
						enemyPopulation--;
						printf("enemyPopulation: %d\n", enemyPopulation);
					}
				}
			}
		}
	}

	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (circleToCircle(enemy[j].attackRange, hero.collider))
		{
			isFightWithAlly[j] = TRUE;
			enemy[j].moveSpeed = 0;

			if (unitAttackTimeElapsed(unitAttackTimer, enemy[j].attackCoolDown, j))
			{
				hero.currentHP -= enemy[j].attackDamage;
				//printf("hero hp: %d", hero.currentHP);
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
			if (unitAttackTimeElapsed(unitAttackTimer, ally[i].attackCoolDown, i))
			{
				ally[i].targetUnit->currentHP -= ally[i].attackDamage;
				//printf("enemy hp: %d\n", ally[i].targetUnit->currentHP);
				if (ally[i].targetUnit->currentHP <= 0)
				{
					if (ally[i].targetUnit->type == WARRIOR)
						allyResource.money += 30;
					else if(ally[i].targetUnit->type == ARCHER)
						allyResource.money += 50;
					ally[i].targetUnit->position = enemyPosition;
					ally[i].targetUnit->alived = FALSE;
					ally[i].targetUnit->collider.radius = 0;
					ally[i].targetUnit->attackRange.radius = 0;

					isFightWithEnemy[i] = FALSE;
					ally[i].targetUnit = NULL;
					if (enemyPopulation > 0)
					{
						enemyPopulation--;
						printf("enemyPopulation: %d\n", enemyPopulation);
					}
				}
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
			if (unitAttackTimeElapsed(unitAttackTimer, enemy[j].attackCoolDown, j))
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
						printf("allyPopulation: %d\n", allyPopulation);
					}
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


			if (unitAttackTimeElapsed(unitAttackTimer, ally[i].attackCoolDown, i))
			{
				enemyBase.currentHP -= ally[i].attackDamage;
				if (enemyBase.currentHP <= 0)
				{
					// 게임 끝 --------스테이지 승리
					CP_Engine_SetNextGameState(StageEndInit, StageEndWInUpdate, StageEndExit);
				}
			}
		}
	}

	UpdateHero(dt);
	UpdateUnits(dt);

	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	DrawEnemyBase();
	DrawHero();
	DrawUnits(ally, unitTest, 19);
	DrawUnits(enemy, unitTest2, 14);

	char heroHP[50] = { 0 };
	sprintf_s(heroHP, _countof(heroHP), "%d / %d", hero.currentHP, hero.maxHP);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText(heroHP, hero.position.x, hero.position.y - 30);

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char allyHP[10][50] = { 0 };
		sprintf_s(allyHP[i], _countof(allyHP[i]), "%d", ally[i].currentHP);
		if(ally[i].alived)
		CP_Font_DrawText(allyHP[i], ally[i].position.x, ally[i].position.y - 30);
	}

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char enemyHP[10][50] = { 0 };
		sprintf_s(enemyHP[i], _countof(enemyHP[i]), "%d", enemy[i].currentHP);
		if (enemy[i].alived)
			CP_Font_DrawText(enemyHP[i], enemy[i].position.x, enemy[i].position.y - 70);
	}
	
	char enemyBaseHP[50] = { 0 };
	sprintf_s(enemyBaseHP, _countof(enemyBaseHP), "%d / %d", enemyBase.currentHP, enemyBase.maxHP);
	CP_Font_DrawText(enemyBaseHP, enemyBase.position.x, enemyBase.position.y - 30);

	char allyMoney[50] = { 0 };
	sprintf_s(allyMoney, _countof(enemyBaseHP), "money: %d", allyResource.money);
	CP_Font_DrawText(allyMoney, 100, 300);

	char allyPop[50] = { 0 };
	sprintf_s(allyPop, _countof(allyPop), "ally Population: %d / %d", allyPopulation, MAX_UNIT);
	CP_Font_DrawText(allyPop, 200, 300);
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