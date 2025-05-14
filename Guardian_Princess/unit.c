#include "unit.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include "utils.h"
#include <stdio.h>
#include "cprocessing.h"
#include "hero.h"
#include "game.h"

Unit ally[MAX_UNIT];
Unit enemy[MAX_UNIT];
int allyPopulation = 0;
int enemyPopulation = 0;
CP_Vector allyPosition;
CP_Vector enemyPosition;


void InitUnit()
{
	CP_Random_Seed((unsigned int)CP_System_GetSeconds());
	allyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 16.0f, CP_System_GetWindowHeight() / 4.0f);
	enemyPosition = CP_Vector_Set(CP_System_GetWindowWidth() * 1.4f, CP_System_GetWindowHeight() / 4.0f);
	allyPopulation = 0;
	enemyPopulation = 0;

	for (int i = 0; i < MAX_UNIT; i++)
	{
		ally[i].position = allyPosition;
		ally[i].alived = FALSE;
		ally[i].moveSpeed = UNIT_SPEED;
		ally[i].collider.radius = 0;
		ally[i].attackRange.position = ally[i].position;
		ally[i].attackRange.radius = 0;
		ally[i].type = WARRIOR;

		ally[i].maxHP = 1;
		ally[i].currentHP = 1;
		ally[i].attackDamage = 0;
		ally[i].attackCoolDown = 1;
		ally[i].price = 1;
		ally[i].targetUnit = NULL;
		ally[i].attackTimer = 0;

		ally[i].animationFrameInfo.frameSlow = 0;
		ally[i].animationFrameInfo.frameCount = 0;
		ally[i].state = WALK;



		//--------------------------------------------

		enemy[i].position = enemyPosition;
		enemy[i].alived = FALSE;
		enemy[i].moveSpeed = UNIT_SPEED;
		enemy[i].collider.radius = 0;
		enemy[i].attackRange.position = enemy[i].position;
		enemy[i].attackRange.radius = 0;
		enemy[i].type = WARRIOR;

		enemy[i].currentHP = 1;
		enemy[i].attackDamage = 0;
		enemy[i].attackCoolDown = 1;
		enemy[i].price = 20;
		enemy[i].targetUnit = NULL;
		enemy[i].attackTimer = 0;

		enemy[i].animationFrameInfo.frameSlow = 0;
		enemy[i].animationFrameInfo.frameCount = 0;
		enemy[i].state = WALK;
	}
}

void SummonUnit(Unit* unit, UnitType type)
{

	int random_num = CP_Random_RangeInt(0, 20) - 10;
	random_num *= 2;

	if (allyPopulation >= MAX_UNIT)
	{
		printf("ally pop: %d", allyPopulation);
		printf("Can't summon ally unit!!!\n");
	}

	else if (unit == ally)
	{
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (!unit[i].alived)
			{
				unit[i].position = allyPosition;
				unit[i].attackRange.radius = 0;
				unit[i].type = type;
				unit[i].collider.position = unit[i].position;
				unit[i].collider.radius = 100;
				unit[i].targetUnit = NULL;
				unit[i].position.y += random_num;
				unit[i].state = WALK;//animation

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 30;
					unit[i].maxHP = 100;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; 

					unit[i].animationStateInfo.Attack.images = allyWarriorAttack;
					unit[i].animationStateInfo.Dead.images = allyWarriorDead;
					unit[i].animationStateInfo.Idle.images = allyWarriorIdle;
					unit[i].animationStateInfo.Walk.images = allyWarriorWalk;

					unit[i].animationStateInfo.Attack.totalframe = 14;
					unit[i].animationStateInfo.Dead.totalframe = 21;
					unit[i].animationStateInfo.Idle.totalframe = 13;
					unit[i].animationStateInfo.Walk.totalframe = 8;



				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 20;
					unit[i].maxHP = 50;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
					unit[i].attackCoolDown = 2.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; 

					unit[i].animationStateInfo.Attack.images = allyArcherAttack; 
					unit[i].animationStateInfo.Dead.images = allyArcherDead; 
					unit[i].animationStateInfo.Idle.images = allyArcherIdle;
					unit[i].animationStateInfo.Walk.images = allyArcherWalk;

					unit[i].animationStateInfo.Attack.totalframe = 8;
					unit[i].animationStateInfo.Dead.totalframe = 18;
					unit[i].animationStateInfo.Idle.totalframe = 22;
					unit[i].animationStateInfo.Walk.totalframe = 16;
				}
				if (allyResource.money - unit[i].price < 0)
				{
					printf("No ally money!!!\n");
					return;
				}
				allyResource.money -= unit[i].price;
				unit[i].alived = TRUE;

				allyPopulation++;
				break;
			}
		}

	}

	if (enemyPopulation >= MAX_UNIT)
	{
		printf("enemy pop: %d\n", enemyPopulation);
		printf("Can't summon enemy unit!!!\n");
	}

	else if (unit == enemy)
	{
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (!unit[i].alived)
			{
				unit[i].position = enemyPosition;
				unit[i].collider.radius = 0;
				unit[i].attackRange.radius = 0;
				unit[i].type = type;
				unit[i].collider.position = unit[i].position;
				unit[i].collider.radius = 120;
				unit[i].targetUnit = NULL;
				unit[i].attackTimer = 3.0f;
				unit[i].position.y += random_num;
				unit[i].state = WALK;//animation

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 34;
					unit[i].maxHP = 100;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; 

					unit[i].animationStateInfo.Attack.images = enemyWarriorAttack;
					unit[i].animationStateInfo.Dead.images = enemyWarriorDead;
					unit[i].animationStateInfo.Idle.images = enemyWarriorIdle;
					unit[i].animationStateInfo.Walk.images = enemyWarriorWalk;

					unit[i].animationStateInfo.Attack.totalframe = 15;
					unit[i].animationStateInfo.Dead.totalframe = 20;
					unit[i].animationStateInfo.Idle.totalframe = 14;
					unit[i].animationStateInfo.Walk.totalframe = 6;
				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 25;
					unit[i].maxHP = 50;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
					unit[i].attackCoolDown = 2.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; 

					unit[i].animationStateInfo.Attack.images = enemyArcherAttack;
					unit[i].animationStateInfo.Dead.images = enemyArcherDead;
					unit[i].animationStateInfo.Idle.images = enemyArcherIdle;
					unit[i].animationStateInfo.Walk.images = enemyArcherWalk;

					unit[i].animationStateInfo.Attack.totalframe = 17;
					unit[i].animationStateInfo.Dead.totalframe = 20;
					unit[i].animationStateInfo.Idle.totalframe = 13;
					unit[i].animationStateInfo.Walk.totalframe = 8;
				}
				if (enemyResource.money - unit[i].price <= 0)
				{
					printf("No enemy money!!!\n");
					return;
				}
				enemyResource.money -= unit[i].price;
				unit[i].alived = TRUE;
				enemyPopulation++;
				break;
			}
		}
	}
}

void UpdateUnits(float dt)
{
	for (int i = 0; i < MAX_UNIT; i++) // animation walk
	{
		if (ally[i].alived)
		{
			ally[i].collider.position = CP_Vector_Set(ally[i].position.x, ally[i].position.y);
			ally[i].attackRange.position = ally[i].collider.position;
			ally[i].position.x += ally[i].moveSpeed * dt;
		}

		if (enemy[i].alived)
		{
			enemy[i].collider.position = CP_Vector_Set(enemy[i].position.x, enemy[i].position.y);
			enemy[i].attackRange.position = enemy[i].collider.position;
			enemy[i].position.x -= enemy[i].moveSpeed * dt;

		}
	}
}



void DrawUnits(Unit* unit) //TODO - 타입 설정
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (unit[i].alived)
		{
			if (unit == ally)
			{
				switch (unit[i].state)
				{
				case ATTACK:
					Animation_play(unit[i].animationStateInfo.Attack.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Attack.totalframe, 1, unit[i].position.x, unit[i].position.y, 256, 256, 255);
					break;
				case WALK:
					Animation_play(unit[i].animationStateInfo.Walk.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Walk.totalframe, 1, unit[i].position.x, unit[i].position.y, 256, 256, 255);
					break;
				case DEAD:
					Animation_play(unit[i].animationStateInfo.Dead.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Dead.totalframe, 1, unit[i].position.x, unit[i].position.y, 256, 256, 255);
					break;
				default:
					Animation_play(unit[i].animationStateInfo.Idle.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Idle.totalframe, 1, unit[i].position.x, unit[i].position.y, 256, 256, 255);
					break;
				}
			}
			else if (unit == enemy)
			{
				switch (unit[i].state)
				{
				case ATTACK:
					Animation_play(unit[i].animationStateInfo.Attack.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Attack.totalframe, 1, unit[i].position.x , unit[i].position.y, -256, 256, 255);
					break;
				case WALK:
					Animation_play(unit[i].animationStateInfo.Walk.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Walk.totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
					break;
				case DEAD:
					Animation_play(unit[i].animationStateInfo.Dead.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Dead.totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
					break;
				default:
					Animation_play(unit[i].animationStateInfo.Idle.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Idle.totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
					break;
				}
			}
		}
	}
}