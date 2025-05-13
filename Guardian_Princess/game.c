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
extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];
extern Bomb bomb;
extern AnimationState heroState;
//-------------------------------------------------------
CP_Image* heroAttack;
CP_Image* heroDead;
CP_Image* heroIdle;
CP_Image* heroWalk;

//CP_Image* allyWarriorIdle;
CP_Image* allyWarriorAttack;
CP_Image* allyWarriorDead;
CP_Image* allyWarriorWalk;

//CP_Image* allyArcherIdle;;
CP_Image* allyArcherAttack;
CP_Image* allyArcherDead;
CP_Image* allyArcherWalk;

//CP_Image* allyWarriorIdle;
CP_Image* enemyWarriorAttack;
CP_Image* enemyWarriorDead;
CP_Image* enemyWarriorWalk;

//CP_Image* allyArcherIdle;;
CP_Image* enemyArcherAttack;
CP_Image* enemyArcherDead;
CP_Image* enemyArcherWalk;
//---------------


UnitSpawner allySpawner[NUM_UNIT_TYPES];
UnitSpawner enemySpawner[NUM_UNIT_TYPES];

Resource allyResource;
Resource enemyResource;

EnemyBase enemyBase;
//-------------------------------------------------------
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image skillButtonImage;

CP_Image battle_background;

CP_Sound battleBGM;
extern Hero hero;
extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];
extern Bomb bomb;
extern AnimationState heroState;
//-------------------------------------------------------
CP_Image* heroAttack;
CP_Image* heroDead;
CP_Image* heroIdle;
CP_Image* heroWalk;

//CP_Image* allyWarriorIdle;
CP_Image* allyWarriorAttack;
CP_Image* allyWarriorDead;
CP_Image* allyWarriorWalk;

//CP_Image* allyArcherIdle;;
CP_Image* allyArcherAttack;
CP_Image* allyArcherDead;
CP_Image* allyArcherWalk;

//CP_Image* allyWarriorIdle;
CP_Image* enemyWarriorAttack;
CP_Image* enemyWarriorDead;
CP_Image* enemyWarriorWalk;

//CP_Image* allyArcherIdle;;
CP_Image* enemyArcherAttack;
CP_Image* enemyArcherDead;
CP_Image* enemyArcherWalk;
//---------------


UnitSpawner allySpawner[NUM_UNIT_TYPES];
UnitSpawner enemySpawner[NUM_UNIT_TYPES];

Resource allyResource;
Resource enemyResource;

EnemyBase enemyBase;
//-------------------------------------------------------
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image skillButtonImage;

CP_Image battle_background;

CP_Sound battleBGM;
>>>>>>> Stashed changes
//-------------------------------------------------------
CP_BOOL isSpawnButtonClicked[NUM_UNIT_TYPES];
CP_BOOL isSkillButtonClicked;
CP_BOOL isSpawnEnemy[NUM_UNIT_TYPES];
CP_BOOL isHeroAttack;
static CP_BOOL skillCoolTimeElasped;
//--------------------------------------------------------
extern CP_Vector allyPosition;
extern CP_Vector enemyPosition;
#define MAX_LINES 100   
#define TEXT_SIZE 50
int r = 0, c = 0; 

int count;


int BGMPlayGame = 1;

typedef struct {
	float number;        // float 媛?
	char text[50]; // 臾몄옄??
} EnemyPattern;

EnemyPattern patterns[MAX_LINES];

CP_Image* unitTest2;

//TODO: 죽으면 spawnTime = 0으로

void GameInit(void)
{

	skillCoolTimeElasped = TRUE;
	r = 0, c = 0;
	CP_System_ShowCursor(FALSE);


	melee_button_image = CP_Image_Load("Assets/In_game/melee.png");
	ranged_button_image = CP_Image_Load("Assets/In_game/ranged.png");
	battle_background = CP_Image_Load("Assets/In_game/battle_background.png");

	heroIdle = Animation_ImageLoader("hero_wait", 4);
	heroAttack = Animation_ImageLoader("hero_attack", 5);
	heroDead = Animation_ImageLoader("hero_dead", 4);
	heroWalk = Animation_ImageLoader("hero_walk", 7);

	//allyWarriorIdle = Animation_ImageLoader("ally_warrior_Idle", 13);
	allyWarriorAttack = Animation_ImageLoader("ally_warrior_Attack", 14);
	allyWarriorDead = Animation_ImageLoader("ally_warrior_Dead", 21);
	allyWarriorWalk = Animation_ImageLoader("ally_warrior_Walk", 14);

	//allyArcherIdle;
	allyArcherAttack = Animation_ImageLoader("ally_archer_Attack", 11);
	allyArcherDead = Animation_ImageLoader("ally_archer_Dead", 18);
	allyArcherWalk = Animation_ImageLoader("ally_archer_Walk", 16);


	//enemyWarriorIdle;
	enemyWarriorAttack = Animation_ImageLoader("enemy_warrior_Attack", 2);
	enemyWarriorDead = Animation_ImageLoader("enemy_warrior_Dead", 20);
	enemyWarriorWalk = Animation_ImageLoader("enemy_warrior_walk", 4);


	//enemyArcherIdle;
	enemyArcherAttack = Animation_ImageLoader("enemy_archer_Attack", 5);
	enemyArcherDead = Animation_ImageLoader("enemy_archer_Dead", 20);
	enemyArcherWalk = Animation_ImageLoader("enemy_archer_walk", 15);


	//allyWarriorIdle = Animation_ImageLoader("ally_warrior_Idle", 13);
	allyWarriorAttack = Animation_ImageLoader("ally_warrior_Attack", 14);
	allyWarriorDead = Animation_ImageLoader("ally_warrior_Dead", 21);
	allyWarriorWalk = Animation_ImageLoader("ally_warrior_Walk", 14);

	//allyArcherIdle;
	allyArcherAttack = Animation_ImageLoader("ally_archer_Attack", 11);
	allyArcherDead = Animation_ImageLoader("ally_archer_Dead", 18);
	allyArcherWalk = Animation_ImageLoader("ally_archer_Walk", 16);

	//enemyWarriorIdle;
	enemyWarriorAttack = Animation_ImageLoader("enemy_warrior_Attack", 2);
	enemyWarriorDead = Animation_ImageLoader("enemy_warrior_Dead", 20);
	enemyWarriorWalk = Animation_ImageLoader("enemy_warrior_walk", 4);

	//enemyArcherIdle;
	enemyArcherAttack = Animation_ImageLoader("enemy_archer_Attack", 5);
	enemyArcherDead = Animation_ImageLoader("enemy_archer_Dead", 20);
	enemyArcherWalk = Animation_ImageLoader("enemy_archer_walk", 15);

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

	if (melee_input == 0)
	{
		isSpawnButtonClicked[0] = TRUE;
	}

	if (isSpawnButtonClicked[0])
	{
		if (SpawnTimeElapsed(allySpawner, 1.3f, WARRIOR))
		{
			SummonUnit(ally, WARRIOR);
			isSpawnButtonClicked[0] = FALSE;
		}
	}

	if (range_input == 0)
	{
		isSpawnButtonClicked[1] = TRUE;
	}

	if (isSpawnButtonClicked[1])
	{
		if (SpawnTimeElapsed(allySpawner, 3.0f, ARCHER))
		{
			SummonUnit(ally, ARCHER);
			isSpawnButtonClicked[1] = FALSE;
		}
	}

	if (skill_input == 0 && skillCoolTimeElasped)
	{
		isSkillButtonClicked = TRUE;
		skillCoolTimeElasped = FALSE;
	}
	if (isSkillButtonClicked)
	{
		SummonBomb();
		isSkillButtonClicked = FALSE;
	}
	if (!skillCoolTimeElasped)
	{
		if (AttackTimeElapsed(&hero.skillTimer, bomb.coolDown))
		{
			skillCoolTimeElasped = TRUE;
		}

		char ch = patterns[r].text[c];
		if (ch == '\0')
		{
			c = 0;
			ch = patterns[++r].text[c];
		}
		if (ch == 'm')
		{
			isSpawnEnemy[0] = TRUE;
			isSpawnEnemy[1] = FALSE;
		}
		else if (ch == 'r')
		{
			isSpawnEnemy[1] = TRUE;
			isSpawnEnemy[0] = FALSE;
		}

		if (isSpawnEnemy[0])
		{
			if (SpawnTimeElapsed(enemySpawner, patterns[r].number, WARRIOR))
			{
				SummonUnit(enemy, WARRIOR);
				isSpawnEnemy[0] = FALSE;
				c++;
			}
		}

		if (isSpawnEnemy[1])
		{
			if (SpawnTimeElapsed(enemySpawner, patterns[r].number, ARCHER))
			{
				SummonUnit(enemy, ARCHER);
				isSpawnEnemy[1] = FALSE;
				c++;
			}
		}
	}


	if (range_input == 0)
	{
		SummonUnit(ally, ARCHER);
	}

	if (timeElapsed(enemySpawner, 1.3f, WARRIOR))
	{
		SummonUnit(enemy, WARRIOR);
	}

	if (timeElapsed(enemySpawner, 3.0f, ARCHER))
	{
		SummonUnit(enemy, ARCHER);
	}




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
					CP_Engine_SetNextGameState(StageEndInit, StageEndLoseUpdate, StageEndExit);
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
				// 게임 끝 --------스테이지 승리

				CP_Engine_SetNextGameState(StageEndInit, StageEndWInUpdate, StageEndExit);
			}
		}
	}

	UpdateHero(dt);
	UpdateUnits(dt);
	DrawEnemyBase();

	DrawHero(IDLE);

	DrawUnits(ally);
	DrawUnits(enemy);

	if (bomb.position.y < ally->position.y)
	{
		DrawBomb(dt);
	}
	else if (bomb.alived)
	{
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (enemy[i].alived)
				enemy[i].currentHP -= bomb.damage;
			if (enemy[i].currentHP <= 0)
			{
				enemy[i].alived = FALSE;
				if (enemy[i].type == WARRIOR)
					allyResource.money += 30;
				else if (enemy[i].type == ARCHER)
					allyResource.money += 50;
				if (enemyPopulation > 0)
				{
					enemyPopulation--;
					printf("enemyPopulation: %d\n", enemyPopulation);
				}
			}
		}
		bomb.alived = FALSE;
	}

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
	CP_Image_Free(&melee_button_image);
	CP_Image_Free(&ranged_button_image);
	CP_Image_Free(&battle_background);
	CP_Sound_Free(&battleBGM);
}