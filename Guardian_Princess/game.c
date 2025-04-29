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


extern Hero hero;
UnitSpawner allySpawner[NUM_UNIT_TYPES];
UnitSpawner enemySpawner[NUM_UNIT_TYPES];
Resource allyResource;
Resource enemyResource;
EnemyBase enemyBase;
extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image battle_background;
AttackTimer heroAttackTimer;
CP_BOOL isClicked[NUM_UNIT_TYPES];
CP_BOOL isClickedEnemy[NUM_UNIT_TYPES];
AttackTimer allyAttackTimer[MAX_UNIT]; 
AttackTimer enemyAttackTimer[MAX_UNIT];

//-------------------------------------------------------
CP_Image* heroAttack;
CP_Image* heroDead;
CP_Image* heroHurt;
CP_Image* heroWait;
CP_Image* heroWalk;

CP_Image* unitTest;
CP_Image* unitTest2;
//--------------------------------------------------------

// Todo: 필요 없는 변수 참조되지 않아도 되는 변수들 지우자 
extern CP_Vector allyPosition;
extern CP_Vector enemyPosition;

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
	SummonEnemyBase();

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

	// Todo: unit spawner cooltime 돌리는 로직 
	//		IsClicked 진짜 필요한 변수 맞아요?????? 
	//		Spawn Timer Logic이 이상해서 어쩔수 없음 --> spawn timer를 고쳐, 이상한 hack 코드 짜지말고!!!
	int melee_input = SquareButtonClicked(melee_button_image, CP_System_GetWindowWidth() / 4.0f * 1, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	int range_input = SquareButtonClicked(ranged_button_image, CP_System_GetWindowWidth() / 4.0f * 3, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);

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

	if (CP_Input_KeyReleased(KEY_1))
	{
		isClickedEnemy[0] = TRUE;
	}

	if (isClickedEnemy[0])
	{
		if (SpawnTimeElapsed(enemySpawner, 1.3f, WARRIOR))
		{
			SummonUnit(enemy, WARRIOR);
			isClickedEnemy[0] = FALSE;
		}
	}

	if (CP_Input_KeyReleased(KEY_3))
	{
		isClickedEnemy[1] = TRUE;
	}

	if (isClickedEnemy[1])
	{
		if (SpawnTimeElapsed(enemySpawner, 3.0f, ARCHER))
		{
			SummonUnit(enemy, ARCHER);
			isClickedEnemy[1] = FALSE;
		}
	}
	// Todo: end of todo


	// hero가 공격할 대상 찾기
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (hero.hero.alived && enemy[j].alived && circleToCircle(hero.hero.attackRange, enemy[j].collider))
		{
			if (hero.hero.targetUnit == NULL)
			{
				hero.hero.targetUnit = &enemy[j];
				break;
			}
		}
	}

	if (hero.hero.alived && hero.hero.targetUnit != NULL && heroAttackTimeElapsed(hero.hero.attackCoolDown))
	{
		hero.hero.targetUnit->currentHP -= hero.hero.attackDamage;
		printf("enemy HP: %d\n", hero.hero.targetUnit->currentHP);
		if (hero.hero.targetUnit->currentHP <= 0)
		{
			hero.hero.targetUnit->alived = FALSE;
			if (enemyPopulation > 0)
			{
				enemyPopulation--;
				printf("enemyPopulation: %d\n", enemyPopulation);
			}
		}
	}

	if (hero.hero.targetUnit && !hero.hero.targetUnit->alived)
		hero.hero.targetUnit = NULL;
	

	// enemy가 hero 때릴 수 있는지 없는지
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].alived && circleToCircle(enemy[j].attackRange, hero.hero.collider))
		{
			if (enemy[j].targetUnit == NULL)
			{
				enemy[j].targetUnit = &hero.hero;
			}

			if (unitAttackTimeElapsed(enemyAttackTimer, enemy[j].attackCoolDown, j))
			{
				hero.hero.currentHP -= enemy[j].attackDamage;
				if (hero.hero.currentHP <= 0)
				{
					printf("hero dead\n");
					hero.hero.collider.radius = 0;
					hero.hero.attackRange.radius = 0;
				}
			}
		}
	}

	//ally find target
	for (int i = 0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (ally[i].alived && enemy[j].alived && circleToCircle(ally[i].attackRange, enemy[j].collider))
			{
				if (ally[i].targetUnit == NULL)
				{
					ally[i].targetUnit = &enemy[j];
					printf("\t\t\t %p ally %d -> enemy %d\n", &ally[i], i, j);
				}
			}
		}
	}

	//ally attack target
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived && ally[i].targetUnit != NULL && unitAttackTimeElapsed(allyAttackTimer, ally[i].attackCoolDown, i))
		{
			ally[i].targetUnit->currentHP -= ally[i].attackDamage;
			printf("\t\t\tally %d deal -> enemy %p\n", i, ally[i].targetUnit);
		}
	}

	//enemy find target
	for (int i = 0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (ally[i].alived && enemy[j].alived && circleToCircle(enemy[j].attackRange, ally[i].collider))
			{
				if (enemy[j].targetUnit == NULL || enemy[j].targetUnit == &hero.hero)
				{
					enemy[j].targetUnit = &ally[i];
					printf("\t\t\t %p enemy %d -> ally %d\n", &enemy[j], j, i);
				}
			}
		}
	}

	//enemy attack target
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].alived && enemy[j].targetUnit != NULL && enemy[j].targetUnit != &hero.hero && unitAttackTimeElapsed(enemyAttackTimer, enemy[j].attackCoolDown, j))
		{
			enemy[j].targetUnit->currentHP -= enemy[j].attackDamage;

			printf("\t\t\tenemy %d deal -> ally %p\n", j, enemy[j].targetUnit);
		}
	}

	//enemy update
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].targetUnit && ally[i].targetUnit->currentHP <= 0)
		{
			printf("\t\t\tally %d killed %p\n", i, ally[i].targetUnit);
			ally[i].targetUnit->alived = FALSE;
			// Todo: 뭐? 돈이 복사가 된다고?? 돈 복사 버그
			if (ally[i].targetUnit->type == WARRIOR)
				allyResource.money += 30;
			else if (ally[i].targetUnit->type == ARCHER)
				allyResource.money += 50;
			ally[i].targetUnit = NULL;
			if (enemyPopulation > 0)
			{
				enemyPopulation--;
				printf("enemyPopulation: %d\n", enemyPopulation);
			}
		}
	}

	//ally update
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].targetUnit && enemy[j].targetUnit->currentHP <= 0)
		{
			printf("\t\t\tenemy %d killed %p\n", j, enemy[j].targetUnit);
			enemy[j].targetUnit->alived = FALSE;
			enemy[j].targetUnit = NULL;
			if (allyPopulation > 0)
			{
				allyPopulation--;
				printf("allyPopulation: %d\n", allyPopulation);
			}
		}
	}

	// ally enemybase attack
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived && circleToCircle(ally[i].attackRange, enemyBase.collider) && ally[i].targetUnit == NULL)
		{
			if (unitAttackTimeElapsed(allyAttackTimer, ally[i].attackCoolDown, i))
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

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].targetUnit || circleToCircle(ally[i].attackRange, enemyBase.collider))
			ally[i].moveSpeed = 0;
		else
			ally[i].moveSpeed = UNIT_SPEED;
	}

	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].targetUnit)
			enemy[j].moveSpeed = 0;

		else
			enemy[j].moveSpeed = UNIT_SPEED;
	}

	for (int j = 0; j < MAX_UNIT; j++)
	{
		// 히어로랑 싸우다가 히어로가 뒤로 도망가면 enemy가 멈춰있는 현상을 고치기 위해서 duck tape로 덕지덕지 발라논 코드
		if (enemy[j].targetUnit == &hero.hero && !circleToCircle(enemy[j].attackRange, hero.hero.collider))
			enemy[j].moveSpeed = UNIT_SPEED;
	}

	float dt = CP_System_GetDt();
	UpdateHero(dt);
	UpdateUnits(dt);

	CP_Image_Draw(battle_background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
	CP_Image_Draw(melee_button_image, CP_System_GetWindowWidth() / 4.0f * 1, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	CP_Image_Draw(ranged_button_image, CP_System_GetWindowWidth() / 4.0f * 3, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);

	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);

	DrawEnemyBase();
	DrawHero();
	DrawUnits(ally, unitTest, 19);
	DrawUnits(enemy, unitTest2, 14);



	char heroHP[50] = { 0 };
	sprintf_s(heroHP, _countof(heroHP), "%d / %d", hero.hero.currentHP, hero.maxHP);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText(heroHP, hero.hero.position.x, hero.hero.position.y - 30);

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char allyHP[10][50] = { 0 };
		sprintf_s(allyHP[i], _countof(allyHP[i]), "%d %5.2f", ally[i].currentHP, allyAttackTimer[i].timer);
		if (ally[i].alived)
			CP_Font_DrawText(allyHP[i], ally[i].position.x, ally[i].position.y - 30);
	}

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char enemyHP[10][50] = { 0 };
		sprintf_s(enemyHP[i], _countof(enemyHP[i]), "%d %5.2f", enemy[i].currentHP, enemyAttackTimer[i].timer);
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

	char enemyPop[50] = { 0 };
	sprintf_s(enemyPop, _countof(enemyPop), "enemy Population: %d / %d", enemyPopulation, MAX_UNIT);
	CP_Font_DrawText(enemyPop, 1600, 300);
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