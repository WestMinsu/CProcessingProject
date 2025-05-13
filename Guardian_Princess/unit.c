#include <stdio.h>
#include "unit.h"
#include "constants.h"
#include "resource.h"
#include "utils.h"
<<<<<<< Updated upstream
#include <stdio.h>
#include "FUNC_Animation_Motion.h"
=======
#include "cprocessing.h"
#include "hero.h"
#include "FUNC_Animation_Motion.h"
#include "game.h"
//---------------------------------------------------------------------
>>>>>>> Stashed changes
Unit ally[MAX_UNIT];
Unit enemy[MAX_UNIT];

int allyPopulation = 0;
int enemyPopulation = 0;
<<<<<<< Updated upstream



void InitUnit(void)
{
=======

CP_Vector allyPosition; 
CP_Vector enemyPosition;

//CP_Image* allyWarriorIdle;
extern CP_Image* allyWarriorAttack;
extern CP_Image* allyWarriorDead;
extern CP_Image* allyWarriorWalk;
 
//extern CP_Image* allyArcherIdle;;
extern CP_Image* allyArcherAttack;
extern CP_Image* allyArcherDead;
extern CP_Image* allyArcherWalk;

//extern CP_Image* allyWarriorIdle;
extern CP_Image* enemyWarriorAttack;
extern CP_Image* enemyWarriorDead;
extern CP_Image* enemyWarriorWalk;

//extern CP_Image* allyArcherIdle;;
extern CP_Image* enemyArcherAttack;
extern CP_Image* enemyArcherDead;
extern CP_Image* enemyArcherWalk;

//---------------------------------------------------------------------

void InitUnit()
{
	allyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 16.0f, CP_System_GetWindowHeight() / 4.0f);
	enemyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 4.0f);

	/*allyPopulation = 0;
	enemyPopulation = 0;*/

>>>>>>> Stashed changes
	for (int i = 0; i < MAX_UNIT; i++)
	{
		ally[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
		ally[i].collider.radius = 0;
		ally[i].moveSpeed = UNIT_SPEED;
		ally[i].type = WARRIOR;

		ally[i].currentHP = 1;
		ally[i].attackDamage = 0;
		ally[i].attackSpeed = 0;
		ally[i].attackRange.position = ally[i].position;
		ally[i].attackRange.radius = 0;
		ally[i].price = 1;
		ally[i].targetUnit = NULL;
		ally[i].alived = FALSE;

<<<<<<< Updated upstream
		ally[i].unitSetting.frameCount = 0;
		ally[i].unitSetting.frameSlow = 0;
		ally[i].unitSetting.frameSlowRate = 3;

		enemy[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
=======
		ally[i].state = IDLE;
		ally[i].animationFrameInfo.frameCount = 0;
		ally[i].animationFrameInfo.frameSlow = 0;

		//---------------------------------------------------

		enemy[i].position = enemyPosition;
		enemy[i].alived = FALSE;
		enemy[i].moveSpeed = UNIT_SPEED;
>>>>>>> Stashed changes
		enemy[i].collider.radius = 0;
		enemy[i].moveSpeed = UNIT_SPEED;
		enemy[i].type = WARRIOR;

		enemy[i].currentHP = 1;
		enemy[i].attackDamage = 0;
		enemy[i].attackSpeed = 0;
		enemy[i].attackRange.position = enemy[i].position;
		enemy[i].attackRange.radius = 0;
		enemy[i].price = 20;
		enemy[i].targetUnit = NULL;
<<<<<<< Updated upstream
		enemy[i].alived = FALSE;

		enemy[i].unitSetting.frameCount = 0;
		enemy[i].unitSetting.frameSlow = 0;
		enemy[i].unitSetting.frameSlowRate = 6;
=======
		enemy[i].attackTimer = 0;

		enemy[i].state = IDLE;
		enemy[i].animationFrameInfo.frameCount = 0;
		enemy[i].animationFrameInfo.frameSlow = 0;
>>>>>>> Stashed changes
	}
}

void SummonUnit(Unit* unit, UnitType type)
{
	if (allyPopulation >= MAX_UNIT)
	{
		printf("%d", allyPopulation);
		printf("Can't summon ally unit!!!\n");
	}
	else if (unit == ally)
	{
		if (allyPopulation < MAX_UNIT)
			allyPopulation++;

		unit[allyPopulation - 1].type = type;
		unit[allyPopulation - 1].collider.radius = 30;

		if (unit[allyPopulation - 1].type == WARRIOR)
		{
<<<<<<< Updated upstream
			unit[allyPopulation - 1].attackDamage = 3;
			unit[allyPopulation - 1].currentHP = 100;
			unit[allyPopulation - 1].attackRange.radius = 50;
			unit[allyPopulation - 1].price = 10;
			unit[allyPopulation - 1].unitSetting.frameCount = 0;

=======
			if (!unit[i].alived)
			{
				unit[i].position = allyPosition;
				unit[i].attackRange.radius = 0;
				unit[i].type = type;
				unit[i].collider.position = unit[i].position;
				unit[i].collider.radius = 30;
				unit[i].targetUnit = NULL;
				unit[i].animationFrameInfo.frameCount = 0;
				unit[i].animationFrameInfo.frameSlow = 0;

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 25;
					unit[i].maxHP = 100;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; 

					unit[i].animationStateInfo.Attack.images = allyWarriorAttack;
					unit[i].animationStateInfo.Dead.images = allyWarriorDead;
					unit[i].animationStateInfo.Idle.images;
					unit[i].animationStateInfo.Walk.images = allyWarriorWalk;

					unit[i].animationStateInfo.Attack.totalframe = 14;
					unit[i].animationStateInfo.Dead.totalframe = 21;
					unit[i].animationStateInfo.Idle.totalframe = 0;
					unit[i].animationStateInfo.Walk.totalframe = 14;
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
					unit[i].animationStateInfo.Idle.images;
					unit[i].animationStateInfo.Walk.images = allyArcherWalk;

					unit[i].animationStateInfo.Attack.totalframe = 11;
					unit[i].animationStateInfo.Dead.totalframe = 18;
					unit[i].animationStateInfo.Idle.totalframe = 0;
					unit[i].animationStateInfo.Walk.totalframe = 16;
				}


				if (allyResource.money - unit[i].price < 0) //돈 부족
				{
					printf("No ally money!!!\n");
					return;
				}
				allyResource.money -= unit[i].price;
				unit[i].alived = TRUE;

				allyPopulation++;
				break;
			}
>>>>>>> Stashed changes
		}
		else if (unit[allyPopulation - 1].type == ARCHER)
		{
			unit[allyPopulation - 1].attackDamage = 2;
			unit[allyPopulation - 1].currentHP = 100;
			unit[allyPopulation - 1].attackRange.radius = 500;
			unit[allyPopulation - 1].price = 50;
		}
		if (allyResource.money - unit[allyPopulation - 1].price <= 0)
		{
			printf("No ally money!!!\n");
			return;
		}
		allyResource.money -= unit[allyPopulation - 1].price;
		unit[allyPopulation - 1].alived = TRUE;
	}

	if (enemyPopulation >= MAX_UNIT)
	{
		printf("Can't summon enemy unit!!!\n");
	}

	else if (unit == enemy)
	{
<<<<<<< Updated upstream
		if (enemyPopulation < MAX_UNIT)
			enemyPopulation++;

		unit[enemyPopulation - 1].type = type;
		unit[enemyPopulation - 1].collider.radius = 30;

		if (unit[enemyPopulation - 1].type == WARRIOR)
		{
			unit[enemyPopulation - 1].attackDamage = 3;
			unit[enemyPopulation - 1].currentHP = 100;
			unit[enemyPopulation - 1].attackRange.radius = 50;
			unit[enemyPopulation - 1].price = 10;
=======
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (!unit[i].alived)
			{
				unit[i].position = enemyPosition;
				unit[i].collider.radius = 0;
				unit[i].attackRange.radius = 0;
				unit[i].type = type;
				unit[i].collider.position = unit[i].position;
				unit[i].collider.radius = 30;
				unit[i].targetUnit = NULL;
				unit[i].attackTimer = 3.0f;

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 50;
					unit[i].maxHP = 100;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f;

					unit[i].animationStateInfo.Attack.images = enemyWarriorAttack;
					unit[i].animationStateInfo.Dead.images = enemyWarriorDead;
					unit[i].animationStateInfo.Idle.images;
					unit[i].animationStateInfo.Walk.images = enemyWarriorWalk;

					unit[i].animationStateInfo.Attack.totalframe = 2;
					unit[i].animationStateInfo.Dead.totalframe = 20;
					unit[i].animationStateInfo.Idle.totalframe = 0;
					unit[i].animationStateInfo.Walk.totalframe = 4;


				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 34;
					unit[i].maxHP = 50;
					unit[i].currentHP = unit[i].maxHP;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
					unit[i].attackCoolDown = 2.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; 

					unit[i].animationStateInfo.Attack.images = enemyArcherAttack;
					unit[i].animationStateInfo.Dead.images = enemyArcherDead;
					unit[i].animationStateInfo.Idle.images;
					unit[i].animationStateInfo.Walk.images = enemyArcherWalk;

					unit[i].animationStateInfo.Attack.totalframe = 5;
					unit[i].animationStateInfo.Dead.totalframe = 20;
					unit[i].animationStateInfo.Idle.totalframe = 0;
					unit[i].animationStateInfo.Walk.totalframe = 15;
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
>>>>>>> Stashed changes
		}
		else if (unit[enemyPopulation - 1].type == ARCHER)
		{
			unit[enemyPopulation - 1].attackDamage = 2;
			unit[enemyPopulation - 1].currentHP = 100;
			unit[enemyPopulation - 1].attackRange.radius = 500;
			unit[enemyPopulation - 1].price = 50;
		}
		if (enemyResource.money - unit[enemyPopulation - 1].price <= 0)
		{
			printf("No enemy money!!!\n");
			return;
		}
		enemyResource.money -= unit[enemyPopulation - 1].price;
		unit[enemyPopulation - 1].alived = TRUE;
	}
}

void UpdateUnits(float dt)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived)
		{
			ally[i].collider.position = CP_Vector_Set(ally[i].position.x, ally[i].position.y);
			ally[i].attackRange.position = ally[i].collider.position;
			ally[i].position.x += ally[i].moveSpeed * dt;

			if (ally[i].moveSpeed == 0)
			{
				ally[i].state = ATTACK;
			}
			else
			{
				ally[i].state = WALK;
			}
		}

		if (enemy[i].alived)
		{
			enemy[i].collider.position = CP_Vector_Set(enemy[i].position.x, enemy[i].position.y);
			enemy[i].attackRange.position = enemy[i].collider.position;
			enemy[i].position.x -= enemy[i].moveSpeed * dt;

			if (enemy[i].moveSpeed== 0)
			{
				enemy[i].state = ATTACK;
			}
			else
			{
				enemy[i].state = WALK;
			}
		}
	}
}

<<<<<<< Updated upstream
void DrawUnits(Unit* unit, CP_Image*unitani, int totalframe)
=======
void DrawUnits(Unit* unit) 
>>>>>>> Stashed changes
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (unit[i].alived)
		{
			if (unit[i].type == WARRIOR)
			{
				if (unit == ally)
				{
<<<<<<< Updated upstream

					Animation_play(unitani, &unit[i].unitSetting , totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
				}
				else if (unit == enemy)
				{
					Animation_play(unitani, &unit[i].unitSetting, totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
=======
					switch (unit[i].state)
					{
					case ATTACK:
						Animation_play(unit[i].animationStateInfo.Attack.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Attack.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					case WALK:
						Animation_play(unit[i].animationStateInfo.Walk.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Walk.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					case DEAD:
						Animation_play(unit[i].animationStateInfo.Dead.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Dead.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					case IDLE:
						Animation_play(unit[i].animationStateInfo.Idle.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Idle.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					}
				}
				else if (unit == enemy)
				{
					switch (unit[i].state)
					{
					case ATTACK:
						Animation_play(unit[i].animationStateInfo.Attack.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Attack.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					case WALK:
						Animation_play(unit[i].animationStateInfo.Walk.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Walk.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					case DEAD:
						Animation_play(unit[i].animationStateInfo.Dead.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Dead.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					case IDLE:
						Animation_play(unit[i].animationStateInfo.Idle.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Idle.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					}
>>>>>>> Stashed changes
				}
			}
			else if (unit[i].type == ARCHER)
			{

				if (unit == ally)
<<<<<<< Updated upstream
					Animation_play(unitani, &unit[i].unitSetting, totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
				else if (unit == enemy)
				{
					Animation_play(unitani, &unit[i].unitSetting,totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
=======
				{
					switch (unit[i].state)
					{
					case ATTACK:
						Animation_play(unit[i].animationStateInfo.Attack.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Attack.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					case WALK:
						Animation_play(unit[i].animationStateInfo.Walk.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Walk.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					case DEAD:
						Animation_play(unit[i].animationStateInfo.Dead.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Dead.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					case IDLE:
						Animation_play(unit[i].animationStateInfo.Idle.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Idle.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
						break;
					}
				}
				else if (unit == enemy)
				{
					switch (unit[i].state)
					{
					case ATTACK:
						Animation_play(unit[i].animationStateInfo.Attack.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Attack.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					case WALK:
						Animation_play(unit[i].animationStateInfo.Walk.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Walk.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					case DEAD:
						Animation_play(unit[i].animationStateInfo.Dead.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Dead.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					case IDLE:
						Animation_play(unit[i].animationStateInfo.Idle.images, &unit[i].animationFrameInfo.frameCount, &unit[i].animationFrameInfo.frameSlow, unit[i].animationStateInfo.Idle.totalframe, 1, unit[i].position.x, unit[i].position.y, -128, 128, 255);
						break;
					}
>>>>>>> Stashed changes
				}
			}
		

		}
	}
}