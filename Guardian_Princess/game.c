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
#include "skill.h"

extern Hero hero;
UnitSpawner allySpawner[NUM_UNIT_TYPES];
UnitSpawner enemySpawner[NUM_UNIT_TYPES];
Resource allyResource;
Resource enemyResource;
EnemyBase enemyBase;
extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];
extern Bomb bomb;
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image skillButtonImage;
CP_Sound battleBGM;
CP_Image battle_background;
CP_BOOL isSpawnButtonClicked[NUM_UNIT_TYPES];
CP_BOOL isSkillButtonClicked;
CP_BOOL isSpawnEnemy[NUM_UNIT_TYPES];
CP_BOOL isHeroAttack;

//-------------------------------------------------------
CP_Image* heroAttack;
CP_Image* heroDead;
CP_Image* heroHurt;
CP_Image* heroWait;
CP_Image* heroWalk;

AnimationDesc unitTest;
AnimationDesc unitTest2;
AnimationDesc enemyRangedImages;
AnimationDesc allyRangedImages;
static CP_BOOL skillCoolTimeElasped;
//--------------------------------------------------------

// Todo: �ʿ� ���� ���� �������� �ʾƵ� �Ǵ� ������ ������ 
extern CP_Vector allyPosition;
extern CP_Vector enemyPosition;
#define MAX_LINES 100   
#define TEXT_SIZE 50
int r = 0, c = 0; 

typedef struct {
	float number;        // float 값
	char text[50]; // 문자열
} EnemyPattern;

int count;
EnemyPattern patterns[MAX_LINES];
int BGMPlayGame = 1;

void GameInit(void)
{
	skillCoolTimeElasped = TRUE;
	r = 0, c = 0;
	CP_System_ShowCursor(FALSE);

	//���� �ε� ----------------------------------

	melee_button_image = CP_Image_Load("Assets/In_game/melee.png");
	ranged_button_image = CP_Image_Load("Assets/In_game/ranged.png");
	skillButtonImage = CP_Image_Load("Assets/In_game/skill.png");
	battle_background = CP_Image_Load("Assets/In_game/battle_background.png");

	heroAttack = Animation_ImageLoader("hero_attack", 5);
	heroDead = Animation_ImageLoader("hero_dead", 4);
	heroHurt = Animation_ImageLoader("hero_hurt", 1);
	heroWait = Animation_ImageLoader("hero_wait", 5);
	heroWalk = Animation_ImageLoader("hero_walk", 7);

	unitTest.totalframe = 19;
	unitTest.images = Animation_ImageLoader("unit_test", unitTest.totalframe);

	unitTest2.totalframe = 14;
	unitTest2.images = Animation_ImageLoader("unit_test2", unitTest2.totalframe);

	battleBGM = CP_Sound_Load("Assets/In_game/batte_bgm.mp3");

	enemyRangedImages.totalframe = 6;
	enemyRangedImages.images = Animation_ImageLoader("enemy_ranged", enemyRangedImages.totalframe);

	allyRangedImages.totalframe = 8;
	allyRangedImages.images = Animation_ImageLoader("test11", allyRangedImages.totalframe);

	InitEnemyBase();
	InitHero();
	InitUnit();
	InitBomb();
	SummonEnemyBase();

	for (int i = 0; i < NUM_UNIT_TYPES; i++)
	{
		allySpawner[i].timer = 0;
		enemySpawner[i].timer = 0;
		isSpawnButtonClicked[i] = FALSE;
		isSpawnEnemy[i] = FALSE;
		isSkillButtonClicked = FALSE;
	}

	allyResource.money = 50;
	enemyResource.money = 10000;

	red = CP_Color_CreateHex(0xFF0000FF);
	green = CP_Color_CreateHex(0x00FF00FF);
	blue = CP_Color_CreateHex(0x0000FFFF);
	white = CP_Color_CreateHex(0xFFFFFFFF);
	pink = CP_Color_CreateHex(0xF08080FF);

	CP_Settings_TextSize(40.0f);
	FILE* file = fopen("data/enemypattern.txt", "r");
	if (file == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	// 구조체 배열과 카운터 선언

	for (int i = 0; i < MAX_LINES; i++)
	{
		patterns[i].number = 0;
		for (int j = 0; j < TEXT_SIZE; j++)
			patterns[i].text[j] = '\0';
	}

	count = 0;
	char line[100];  // 한 줄을 읽을 버퍼

	while (fgets(line, sizeof(line), file) != NULL && count < MAX_LINES) {
		// 줄 끝의 개행문자 제거
		line[strcspn(line, "\r\n")] = 0;

		// 선행 및 후행 공백 제거
		char* start = line;
		while (isspace((unsigned char)*start)) start++;
		char* end = start + strlen(start);
		while (end > start && isspace((unsigned char)*(end - 1))) end--;
		*end = '\0';

		// 빈 줄 건너뛰기
		if (strlen(start) == 0) {
			printf("빈 줄 발견\n");
			continue;
		}

		// 파싱 시도
		EnemyPattern temp;
		if (sscanf_s(start, "%f %49s", &temp.number, temp.text, (unsigned)_countof(temp.text)) == 2) {
			patterns[count] = temp;
			count++;
		}
		else {
			printf("잘못된 줄 (내용: '%s')\n", start);
		}
	}

	// 파일 닫기
	fclose(file);
}

void GameUpdate(void)
{
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}

	// Todo: unit spawner cooltime ������ ���� 
	//		IsClicked ��¥ �ʿ��� ���� �¾ƿ�?????? 
	//		Spawn Timer Logic�� �̻��ؼ� ��¿�� ���� --> spawn timer�� ����, �̻��� hack �ڵ� ¥������!!!
	int melee_input = SquareButtonClicked(melee_button_image, CP_System_GetWindowWidth() / 4.0f * 1, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	int range_input = SquareButtonClicked(ranged_button_image, CP_System_GetWindowWidth() / 4.0f * 2, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	int skill_input = SquareButtonClicked(skillButtonImage, CP_System_GetWindowWidth() / 4.0f * 3, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);

	if (melee_input == 0)
	{
		isSpawnButtonClicked[0] = TRUE;
	}

	if (isSpawnButtonClicked[0])
	{
		if (SpawnTimeElapsed(allySpawner, 1.3f, WARRIOR))
		{
			SummonUnit(ally, WARRIOR, unitTest);
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
			SummonUnit(ally, ARCHER, allyRangedImages);
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
	}

	if (BGMPlayGame == 1)
	{
		CP_Sound_PlayAdvanced(battleBGM, 1.0f, 1.0f, 1, BGM);
		BGMPlayGame = 0;
	}

	float dt = CP_System_GetDt();

	if (enemyPopulation < MAX_UNIT)
	{
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
				SummonUnit(enemy, WARRIOR, unitTest2);
				isSpawnEnemy[0] = FALSE;
				c++;
			}
		}

		if (isSpawnEnemy[1])
		{
			if (SpawnTimeElapsed(enemySpawner, patterns[r].number, ARCHER))
			{
				SummonUnit(enemy, ARCHER, enemyRangedImages);
				isSpawnEnemy[1] = FALSE;
				c++;
			}
		}
	}

	// hero attack using spacekey
	if (CP_Input_KeyReleased(KEY_SPACE))
	{
		isHeroAttack = TRUE;
	}

	if (isHeroAttack)
	{
		if (AttackTimeElapsed(&hero.hero.attackTimer, hero.hero.attackCoolDown))
		{
			for (int j = 0; j < MAX_UNIT; j++)
			{
				if (hero.hero.alived && enemy[j].alived && circleToCircle(hero.hero.attackRange, enemy[j].collider))
				{
					enemy[j].currentHP -= hero.hero.attackDamage;
					isHeroAttack = FALSE;
					if (enemy[j].currentHP <= 0)
					{
						enemy[j].alived = FALSE;
						if (enemyPopulation > 0)
						{
							enemyPopulation--;
		
						}
					}
				}
				else
					isHeroAttack = FALSE;
			}
		}
	}

	// enemy�� hero ���� �� �ִ��� ������
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].alived && circleToCircle(enemy[j].attackRange, hero.hero.collider))
		{
			if (enemy[j].targetUnit == NULL)
			{
				enemy[j].targetUnit = &hero.hero;
			}

			if (AttackTimeElapsed(&enemy[j].attackTimer, enemy[j].attackCoolDown))
			{
				hero.hero.currentHP -= enemy[j].attackDamage;
				if (hero.hero.currentHP <= 0)
				{
					CP_Engine_SetNextGameState(StageEndInit, StageEndLoseUpdate, StageEndExit);
					printf("hero dead\n");
					hero.hero.moveSpeed = 0;
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
		if (ally[i].alived && ally[i].targetUnit != NULL && AttackTimeElapsed(&ally[i].attackTimer, ally[i].attackCoolDown))
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
		if (enemy[j].alived && enemy[j].targetUnit != NULL && enemy[j].targetUnit != &hero.hero && AttackTimeElapsed(&enemy[j].attackTimer, enemy[j].attackCoolDown))
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
			if (ally[i].targetUnit->alived)
			{
				ally[i].targetUnit->alived = FALSE;
				if (ally[i].targetUnit->type == WARRIOR)
					allyResource.money += 10;
				else if (ally[i].targetUnit->type == ARCHER)
					allyResource.money += 20;
				if (enemyPopulation > 0)
				{
					enemyPopulation--;
					printf("enemyPopulation: %d\n", enemyPopulation);
				}
			}
			ally[i].targetUnit = NULL;
		}
	}

	//ally update
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].targetUnit && enemy[j].targetUnit->currentHP <= 0)
		{
			printf("\t\t\tenemy %d killed %p\n", j, enemy[j].targetUnit);
			if (enemy[j].targetUnit->alived)
			{
				enemy[j].targetUnit->alived = FALSE;
				if (allyPopulation > 0)
				{
					allyPopulation--;
				}
			}
			enemy[j].targetUnit = NULL;
		}
	}

	// ally enemybase attack
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived && circleToCircle(ally[i].attackRange, enemyBase.collider) && ally[i].targetUnit == NULL)
		{
			if (AttackTimeElapsed(&ally[i].attackTimer, ally[i].attackCoolDown))
			{
				enemyBase.currentHP -= ally[i].attackDamage;
				if (enemyBase.currentHP <= 0)
				{
					// ���� �� --------�������� �¸�
			
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
		// ����ζ� �ο�ٰ� ����ΰ� �ڷ� �������� enemy�� �����ִ� ������ ��ġ�� ���ؼ� duck tape�� �������� �߶�� �ڵ�
		if (enemy[j].targetUnit == &hero.hero && !circleToCircle(enemy[j].attackRange, hero.hero.collider))
			enemy[j].moveSpeed = UNIT_SPEED;
	}


	UpdateHero(dt);
	UpdateUnits(dt);

	CP_Image_Draw(battle_background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 1.0f, 255);
	CP_Image_Draw(melee_button_image, CP_System_GetWindowWidth() / 4.0f * 1, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	CP_Image_Draw(ranged_button_image, CP_System_GetWindowWidth() / 4.0f * 2, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	CP_Image_Draw(skillButtonImage, CP_System_GetWindowWidth() / 4.0f * 3, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);

	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;
	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);

	DrawEnemyBase();
	DrawHero();
	DrawUnits(ally, 19);
	DrawUnits(enemy, 14);
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
	sprintf_s(heroHP, _countof(heroHP), "%d  %5.2f", hero.hero.currentHP, hero.hero.attackTimer);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText(heroHP, hero.hero.position.x - 30, hero.hero.position.y - 50);

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char allyHP[10][50] = { 0 };
		sprintf_s(allyHP[i], _countof(allyHP[i]), "%d %5.2f", ally[i].currentHP, ally[i].attackTimer);
		if (ally[i].alived)
		{
			CP_Font_DrawText(allyHP[i], ally[i].position.x, ally[i].position.y - 50);
			CP_Graphics_DrawRect(ally[i].position.x, ally[i].position.y - 30, CP_System_GetWindowWidth() / 16.0f * ((float)ally[i].currentHP / ally[i].maxHP), 10);
		}
	}

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char enemyHP[10][50] = { 0 };
		sprintf_s(enemyHP[i], _countof(enemyHP[i]), "%d %5.2f", enemy[i].currentHP, enemy[i].attackTimer);
		if (enemy[i].alived)
		{
			CP_Font_DrawText(enemyHP[i], enemy[i].position.x, enemy[i].position.y - 90);
			CP_Graphics_DrawRect(enemy[i].position.x, enemy[i].position.y - 70, CP_System_GetWindowWidth() / 16.0f * ((float)enemy[i].currentHP / enemy[i].maxHP), 10);
		}
	}

	char enemyBaseHP[50] = { 0 };
	sprintf_s(enemyBaseHP, _countof(enemyBaseHP), "%d / %d", enemyBase.currentHP, enemyBase.maxHP);
	CP_Font_DrawText(enemyBaseHP, enemyBase.position.x-30, enemyBase.position.y - 125);

	char allyMoney[50] = { 0 };
	sprintf_s(allyMoney, _countof(enemyBaseHP), "money: %d", allyResource.money);
	CP_Font_DrawText(allyMoney, 100, 300);

	char allyPop[50] = { 0 };
	sprintf_s(allyPop, _countof(allyPop), "ally Population: %d / %d", allyPopulation, MAX_UNIT);
	CP_Font_DrawText(allyPop, 200, 300);

	char enemyPop[50] = { 0 };
	sprintf_s(enemyPop, _countof(enemyPop), "enemy Population: %d / %d", enemyPopulation, MAX_UNIT);
	CP_Font_DrawText(enemyPop, 1600, 100);

	char allySpawnTime1[50] = { 0 };
	sprintf_s(allySpawnTime1, _countof(allySpawnTime1), "%5.2f", WARRIOR_SPAWN_TIME - allySpawner[WARRIOR].timer);
	CP_Font_DrawText(allySpawnTime1, 500, 500);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4.0f * 1.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f - 140, CP_System_GetWindowWidth() / 8.0f - CP_System_GetWindowWidth() / 8.0f * (allySpawner[WARRIOR].timer / WARRIOR_SPAWN_TIME), 10);

	char allySpawnTime2[50] = { 0 };
	sprintf_s(allySpawnTime2, _countof(allySpawnTime2), "%5.2f", ARCHER_SPAWN_TIME - allySpawner[ARCHER].timer);
	CP_Font_DrawText(allySpawnTime2, 700, 500);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4.0f * 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f - 140, CP_System_GetWindowWidth() / 8.0f - CP_System_GetWindowWidth() / 8.0f * (allySpawner[ARCHER].timer / ARCHER_SPAWN_TIME), 10);

	char enemySpawnTime1[50] = { 0 };

	sprintf_s(enemySpawnTime1, _countof(enemySpawnTime1), "%5.2f", enemySpawner[WARRIOR].timer);
	CP_Font_DrawText(enemySpawnTime1, 1200, 500);

	char enemySpawnTime2[50] = { 0 };
	sprintf_s(enemySpawnTime2, _countof(enemySpawnTime2), "%5.2f", enemySpawner[ARCHER].timer);
	CP_Font_DrawText(enemySpawnTime2, 1400, 500);

	char bombTime[50] = { 0 };
	sprintf_s(bombTime, _countof(bombTime), "bomb timer: %5.2f", hero.skillTimer);
	CP_Font_DrawText(bombTime, 1000, 500);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4.0f * 3.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f - 140, CP_System_GetWindowWidth() / 8.0f - CP_System_GetWindowWidth() / 8.0f * (hero.skillTimer / bomb.coolDown), 10);
}

void GameExit(void)
{
	CP_Sound_Free(&battleBGM);
	BGMPlayGame = 1;

}