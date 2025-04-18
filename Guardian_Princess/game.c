#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <stdio.h>
#include "game.h"

#define HERO_SPEED 400
#define MAX_UNIT 10
#define NUM_ENEMY_TYPES 2
#define UNIT_SPEED 200

extern CP_Image cursorImage;
CP_BOOL cursor;
CP_Color red;
CP_Color green;
CP_Color blue;
CP_Color white;
static float dt;

Hero hero;
Ally ally[MAX_UNIT];
AllySpawner allySpawner[MAX_UNIT];
Enemy enemy[MAX_UNIT];
EnemySpawner enemySpawner[NUM_ENEMY_TYPES];

void initHero(void)
{
	hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
	hero.collider.radius = 30;
	hero.moveSpeed = UNIT_SPEED;

	hero.hp = 1000;
	hero.attackDamage = 0;
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

void SummonAllyUnit(void)
{
	static int idx = 0;

	printf("index: %d\n", idx);

	if (idx >= MAX_UNIT)
	{
		printf("Can't summon ally unit!!!\n");

		return;
	}

	ally[idx].collider.radius = 30;
	ally[idx].attackRange.radius = 50;
	ally[idx].alived = TRUE;
	idx++;
}

void SummonEnemyUnit(EnemyType type)
{
	static int idx = 0;

	//printf("index: %d\n", idx);

	if (idx >= MAX_UNIT)
	{
		printf("Can't summon enemy unit!!!\n");
		return;
	}

	enemy[idx].collider.radius = 30;
	enemy[idx].attackRange.radius = 50;
	enemy[idx].type = type;

	if (enemy[idx].type == RANGED)
	{
		enemy[idx].attackRange.radius = 200;
	}

	enemy[idx].alived = TRUE;


	idx++; 

}

void DrawHero(void)
{
	CP_Settings_Fill(green);
	CP_Graphics_DrawCircle(hero.position.x, hero.position.y, 30);

	hero.collider.position = CP_Vector_Set(hero.position.x, hero.position.y);
	hero.attackRange.position = hero.collider.position;
	if (CP_Input_KeyDown(KEY_A))
	{
		hero.position.x -= HERO_SPEED * dt;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		hero.position.x += HERO_SPEED * dt;
	}
}

//TODO: Á×À¸¸é spawnTime = 0À¸·Î

void DrawAllyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived)
		{
			CP_Settings_Fill(blue);
			CP_Graphics_DrawCircle(ally[i].position.x, ally[i].position.y, 30);

			ally[i].collider.position = CP_Vector_Set(ally[i].position.x, ally[i].position.y);
			ally[i].attackRange.position = ally[i].collider.position;
			ally[i].position.x += ally[i].moveSpeed * dt;

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
			enemy[i].attackRange.position = enemy[i].collider.position;
			enemy[i].position.x -= enemy[i].moveSpeed * dt;
		}
	}
}

void GameInit(void)
{
	CP_System_ShowCursor(cursor);

	initHero();
	initUnit();

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

	if (IsAreaClicked(summonButton_x, summonButton_y, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		SummonAllyUnit();
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
	for (int i=0; i < MAX_UNIT; i++)
	{
		for (int j = 0; j < MAX_UNIT; j++)
		{
			if (circleToCircle(hero.attackRange, enemy[j].collider))
			{
				//printf("as");
				enemy[j].hp -= hero.attackDamage;
				if (enemy[j].hp <= 0)
				{
					enemy[j].alived = FALSE;
					enemy[j].collider.radius = 0;
					enemy[j].attackRange.radius = 0;
				}
			}

			if (circleToCircle(enemy[j].attackRange, hero.collider))
			{
				printf("zz");
				enemy[j].moveSpeed = 0;

				hero.hp -= enemy[j].attackDamage;
				if (hero.hp <= 0)
				{
					hero.moveSpeed = 0;
					hero.collider.radius = 0;
					hero.attackRange.radius = 0;
				}
			}

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
	
	CP_Image_Draw(cursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	DrawHero();
	DrawAllyUnits();
	DrawEnemyUnits();
}

void GameExit(void)
{

}