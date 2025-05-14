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
#include "camera.h"

extern Hero hero;
UnitSpawner allySpawner[NUM_UNIT_TYPES];
UnitSpawner enemySpawner[NUM_UNIT_TYPES];
Resource allyResource;
Resource enemyResource;
EnemyBase enemyBase;
extern Unit ally[MAX_UNIT];
extern Unit enemy[MAX_UNIT];
extern Bomb bomb;
//-------------------------------------------------------
CP_Image melee_button_image;
CP_Image ranged_button_image;
CP_Image skillButtonImage;
CP_Image battle_background;
CP_Image coin_image;
CP_Image population_image;
CP_Image explosion_image;
//-------------------------------------------------------
CP_Sound battleBGM;
//-------------------------------------------------------
CP_BOOL isSpawnButtonClicked[NUM_UNIT_TYPES];
CP_BOOL isSkillButtonClicked;
CP_BOOL isSpawnEnemy[NUM_UNIT_TYPES];
CP_BOOL isHeroAttack;
//-------------------------------------------------------
static CP_BOOL skillCoolTimeElasped;
//--------------------------------------------------------
CP_Image* heroAttack;
CP_Image* heroDead;
CP_Image* heroIdle;
CP_Image* heroWalk;

CP_Image* allyArcherAttack;
CP_Image* allyArcherDead;
CP_Image* allyArcherIdle;
CP_Image* allyArcherWalk;

CP_Image* allyWarriorAttack;
CP_Image* allyWarriorDead;
CP_Image* allyWarriorIdle;
CP_Image* allyWarriorWalk;

CP_Image* enemyArcherAttack;
CP_Image* enemyArcherDead;
CP_Image* enemyArcherIdle;
CP_Image* enemyArcherWalk;

CP_Image* enemyWarriorAttack;
CP_Image* enemyWarriorDead;
CP_Image* enemyWarriorIdle;
CP_Image* enemyWarriorWalk;
//--------------------------------------------------------

extern CP_Vector allyPosition;
extern CP_Vector enemyPosition;
CP_Matrix cameraMatrix;
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

CP_Vector cameraPos;
float zoom;
float speed;

int currentFrame = 0;
float frameTimer = 0.0f;
float frameDuration = 0.1f;
CP_BOOL exploded;

void GameInit(void)
{
	zoom = 1.0f;
	speed = 200.0f;

	cameraPos = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);

	skillCoolTimeElasped = TRUE;
	exploded = FALSE;
	r = 0, c = 0;
	CP_System_ShowCursor(FALSE);

	//���� �ε� ----------------------------------
	melee_button_image = CP_Image_Load("Assets/In_game/annie.png");
	ranged_button_image = CP_Image_Load("Assets/In_game/parasoul.png");
	skillButtonImage = CP_Image_Load("Assets/In_game/skill.png");
	battle_background = CP_Image_Load("Assets/In_game/battle_background.png");
	coin_image = CP_Image_Load("Assets/In_game/coin.png");
	population_image = CP_Image_Load("Assets/In_game/population.png");
	explosion_image = CP_Image_Load("Assets/In_game/explosion.png");

	battleBGM = CP_Sound_Load("Assets/In_game/batte_bgm.mp3");

	heroAttack = Animation_ImageLoader("hero_Attack", 5);
	heroDead = Animation_ImageLoader("hero_Dead", 4);
	heroIdle = Animation_ImageLoader("hero_Idle", 5);
	heroWalk = Animation_ImageLoader("hero_Walk", 7);

	allyArcherAttack = Animation_ImageLoader("ally_archer_Attack",8);
	allyArcherDead = Animation_ImageLoader("ally_archer_Dead", 18);
	allyArcherIdle = Animation_ImageLoader("ally_archer_Idle", 22);
	allyArcherWalk = Animation_ImageLoader("ally_archer_Walk", 16);

	allyWarriorAttack = Animation_ImageLoader("ally_warrior_Attack", 14);
	allyWarriorDead = Animation_ImageLoader("ally_warrior_Dead", 21);
	allyWarriorIdle = Animation_ImageLoader("ally_warrior_Idle", 13);
	allyWarriorWalk = Animation_ImageLoader("ally_warrior_Walk", 8);

	enemyArcherAttack = Animation_ImageLoader("enemy_archer_Attack", 17);
	enemyArcherDead = Animation_ImageLoader("enemy_archer_Dead", 20);
	enemyArcherIdle = Animation_ImageLoader("enemy_archer_Idle", 11);
	enemyArcherWalk = Animation_ImageLoader("enemy_archer_Walk", 15);

	enemyWarriorAttack = Animation_ImageLoader("enemy_Warrior_Attack", 15);
	enemyWarriorDead = Animation_ImageLoader("enemy_Warrior_Dead", 20);
	enemyWarriorIdle = Animation_ImageLoader("enemy_Warrior_Idle", 14);
	enemyWarriorWalk = Animation_ImageLoader("enemy_Warrior_Walk", 6);

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
	black = CP_Color_CreateHex(0x000000FF);

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
	cameraMatrix = GetCameraMatrix(cameraPos, zoom);

	if (CP_Input_KeyDown(KEY_ESCAPE))
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);


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
		if (SpawnTimeElapsed(allySpawner, 2.0f, ARCHER))
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

	// hero attack using spacekey
	if (CP_Input_KeyReleased(KEY_SPACE))
	{
		isHeroAttack = TRUE;
	}

	if (isHeroAttack)
	{
		hero.hero.state = ATTACK; //영웅 공격

		if (AttackTimeElapsed(&hero.hero.attackTimer, hero.hero.attackCoolDown))
		{
			hero.hero.state = IDLE;
			for (int j = 0; j < MAX_UNIT; j++)
			{
				if (hero.hero.alived && enemy[j].alived && circleToCircle(hero.hero.attackRange, enemy[j].collider))
				{
					enemy[j].currentHP -= hero.hero.attackDamage;
					isHeroAttack = FALSE;
					if (enemy[j].currentHP <= 0)
					{
						enemy[j].state = DEAD; //animation DEAD
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

			enemy[j].state = ATTACK;
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
		else
		{
			enemy[j].state = WALK;
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

	//ally attack target //animation attack state
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived && ally[i].targetUnit != NULL)
		{
			ally[i].state = ATTACK;
			if (AttackTimeElapsed(&ally[i].attackTimer, ally[i].attackCoolDown))
			{
				ally[i].targetUnit->currentHP -= ally[i].attackDamage;
				printf("ally attack\n");
				printf("\t\t\tally %d deal -> enemy %p\n", i, ally[i].targetUnit);
			}
		}
		if(ally[i].targetUnit == NULL)
			ally[i].state = WALK;
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

	//enemy attack target //animation attack state
	for (int j = 0; j < MAX_UNIT; j++)
	{
		if (enemy[j].alived && enemy[j].targetUnit != NULL && enemy[j].targetUnit != &hero.hero)
		{
			enemy[j].state = ATTACK;
			if (AttackTimeElapsed(&enemy[j].attackTimer, enemy[j].attackCoolDown))
			{
				enemy[j].targetUnit->currentHP -= enemy[j].attackDamage;
				printf("\t\t\tenemy %d deal -> ally %p\n", j, enemy[j].targetUnit);
			}
		}
		if (enemy[j].targetUnit == NULL)
			enemy[j].state = WALK;
	}

	//enemy update
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].targetUnit && ally[i].targetUnit->currentHP <= 0)
		{
			printf("\t\t\tally %d killed %p\n", i, ally[i].targetUnit);

			if (ally[i].targetUnit->alived)
			{
				ally[i].targetUnit->state = DEAD; // animation dead
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
				ally[i].state = WALK; ///animation attack end
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
				enemy[j].targetUnit->state = DEAD; //animation dead
				enemy[j].targetUnit->alived = FALSE;
				if (allyPopulation > 0)
				{
					allyPopulation--;
				}
			}
			enemy[j].targetUnit = NULL;
			enemy[j].state = WALK; ///animation attack end
		}
	}

	// ally enemybase attack
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived && circleToCircle(ally[i].attackRange, enemyBase.collider) && ally[i].targetUnit == NULL)
		{
			ally[i].state = ATTACK;
			if (AttackTimeElapsed(&ally[i].attackTimer, ally[i].attackCoolDown))
			{
				enemyBase.currentHP -= ally[i].attackDamage;
				if (enemyBase.currentHP <= 0)
				{
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
		if (enemy[j].targetUnit == &hero.hero && !circleToCircle(enemy[j].attackRange, hero.hero.collider))
			enemy[j].moveSpeed = UNIT_SPEED;
	}

	UpdateHero(dt);
	UpdateUnits(dt);


	CP_Graphics_ClearBackground(white);


	// ------------ carmera apply-------------------------
	CP_Settings_ApplyMatrix(cameraMatrix);
	CP_Image_Draw(battle_background, CP_System_GetWindowWidth() / 1.0f, CP_System_GetWindowHeight() / 2.0f, CP_System_GetWindowWidth() * 3.5f, CP_System_GetWindowHeight() / 1.0f, 255);


	float cursorWidth = CP_System_GetWindowWidth() / 25.0f;
	float cursorHeight = CP_System_GetWindowHeight() / 20.0f;

	DrawEnemyBase();


	DrawUnits(ally);
	DrawUnits(enemy);
	DrawHero();

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char allyHP[10][50] = { 0 };
		sprintf_s(allyHP[i], _countof(allyHP[i]), "%d %5.2f", ally[i].currentHP, ally[i].attackTimer);
		if (ally[i].alived)
		{
			CP_Settings_Fill(green);
			CP_Graphics_DrawRect(ally[i].position.x-20, ally[i].position.y - 150, CP_System_GetWindowWidth() / 16.0f * ((float)ally[i].currentHP / ally[i].maxHP) * ally[i].maxHP / 300, 10);
		}
	}

	for (int i = 0; i < MAX_UNIT; i++)
	{
		char enemyHP[10][50] = { 0 };
		sprintf_s(enemyHP[i], _countof(enemyHP[i]), "%d %5.2f", enemy[i].currentHP, enemy[i].attackTimer);
		if (enemy[i].alived)
		{
			CP_Settings_Fill(red);
			CP_Graphics_DrawRect(enemy[i].position.x + 30, enemy[i].position.y - 150, CP_System_GetWindowWidth() / 16.0f * ((float)enemy[i].currentHP / enemy[i].maxHP) * enemy[i].maxHP / 300, 10);
		}
	}

	char heroHP[50] = { 0 };
	sprintf_s(heroHP, _countof(heroHP), "%d", hero.hero.currentHP);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText(heroHP, hero.hero.position.x - 30, hero.hero.position.y - 100);

	char enemyBaseHP[50] = { 0 };
	sprintf_s(enemyBaseHP, _countof(enemyBaseHP), "%d / %d", enemyBase.currentHP, enemyBase.maxHP);
	CP_Font_DrawText(enemyBaseHP, enemyBase.position.x - 30, enemyBase.position.y - 125);

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

		exploded = TRUE;
		bomb.alived = FALSE;
	}

	if (exploded)
	{
		frameTimer += CP_System_GetDt();

		if (frameTimer >= frameDuration)
		{
			currentFrame++;
			frameTimer = 0.0f; // 타이머 초기화
		}

		int imageWidth = CP_Image_GetWidth(explosion_image);
		int imageHeight = CP_Image_GetHeight(explosion_image);

		int row = currentFrame / 3;
		int col = currentFrame % 3;
		if (row == 0)
			CP_Image_DrawSubImage(explosion_image, bomb.position.x, hero.hero.position.y - 120, 2000, 700, (imageWidth * col / 3.0f), (imageHeight * row / 3.0f), (imageWidth * (col + 1) / 3.0f), (imageHeight * (row + 1) / 3.0f), 255);
		else
			CP_Image_DrawSubImage(explosion_image, bomb.position.x, hero.hero.position.y, 2000, 700, (imageWidth * col / 3.0f), (imageHeight * row / 3.0f), (imageWidth * (col + 1) / 3.0f), (imageHeight * (row + 1) / 3.0f), 255);

		if (currentFrame == 8)
		{
			exploded = FALSE;
			currentFrame = 0;
		}
	}

	CP_Settings_ResetMatrix();
	// ---------------------------- camera end ----------------------------

	CP_Image_Draw(melee_button_image, CP_System_GetWindowWidth() / 4.0f * 1, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	CP_Image_Draw(ranged_button_image, CP_System_GetWindowWidth() / 4.0f * 2, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);
	CP_Image_Draw(skillButtonImage, CP_System_GetWindowWidth() / 4.0f * 3, CP_System_GetWindowHeight() / 4.0f * 3.0f, CP_System_GetWindowWidth() / 8.0f, CP_System_GetWindowHeight() / 4.0f, 255);

	char allyMoney[50] = { 0 };
	sprintf_s(allyMoney, _countof(enemyBaseHP), ": %d", allyResource.money);
	CP_Image_Draw(coin_image, 100, 100, 50, 50, 255);
	CP_Font_DrawText(allyMoney, 120, 100);

	char allyPop[50] = { 0 };
	sprintf_s(allyPop, _countof(allyPop), ": %d / %d", allyPopulation, MAX_UNIT);
	CP_Image_Draw(population_image, 100, 150, 40, 40, 255);
	CP_Font_DrawText(allyPop, 120, 150);

	char enemyPop[50] = { 0 };
	sprintf_s(enemyPop, _countof(enemyPop), ": %d / %d", enemyPopulation, MAX_UNIT);
	CP_Font_DrawText(enemyPop, 1670, 100);
	CP_Image_Draw(population_image, 1650, 100, 40, 40, 255);

	char allySpawnTime1[50] = { 0 };
	sprintf_s(allySpawnTime1, _countof(allySpawnTime1), "%5.2f", WARRIOR_SPAWN_TIME - allySpawner[WARRIOR].timer);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4.0f * 1.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f - 140, CP_System_GetWindowWidth() / 8.0f - CP_System_GetWindowWidth() / 8.0f * (allySpawner[WARRIOR].timer / WARRIOR_SPAWN_TIME), 10);

	char allySpawnTime2[50] = { 0 };
	sprintf_s(allySpawnTime2, _countof(allySpawnTime2), "%5.2f", ARCHER_SPAWN_TIME - allySpawner[ARCHER].timer);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4.0f * 2.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f - 140, CP_System_GetWindowWidth() / 8.0f - CP_System_GetWindowWidth() / 8.0f * (allySpawner[ARCHER].timer / ARCHER_SPAWN_TIME), 10);

	char bombTime[50] = { 0 };
	sprintf_s(bombTime, _countof(bombTime), "bomb timer: %5.2f", hero.skillTimer);
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4.0f * 3.0f, CP_System_GetWindowHeight() / 4.0f * 3.0f - 140, CP_System_GetWindowWidth() / 8.0f - CP_System_GetWindowWidth() / 8.0f * (hero.skillTimer / bomb.coolDown), 10);

	CP_Image_Draw(CursorImage, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
}

void GameExit(void)
{
	CP_Sound_Free(&battleBGM);
	BGMPlayGame = 1;
}