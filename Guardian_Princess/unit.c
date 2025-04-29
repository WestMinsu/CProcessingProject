#include "unit.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include "utils.h"
#include <stdio.h>
Unit ally[MAX_UNIT];
Unit enemy[MAX_UNIT];
int allyPopulation = 0;
int enemyPopulation = 0;
CP_Vector allyPosition; // why 전역?? why do you love 전역 변수 so much??? 
CP_Vector enemyPosition;

void InitUnit(void)
{
	allyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 8.0f);
	enemyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
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

		ally[i].currentHP = 1;
		ally[i].attackDamage = 0;
		ally[i].attackCoolDown = 3;
		ally[i].price = 1;
		//ally[i].unitSetting ???
		ally[i].targetUnit = NULL;

		enemy[i].position = enemyPosition;
		enemy[i].alived = FALSE;
		enemy[i].moveSpeed = UNIT_SPEED;
		enemy[i].collider.radius = 0;
		enemy[i].attackRange.position = enemy[i].position;
		enemy[i].attackRange.radius = 0;
		enemy[i].type = WARRIOR;

		enemy[i].currentHP = 1;
		enemy[i].attackDamage = 0;
		enemy[i].attackCoolDown = 5;
		enemy[i].price = 20;
		// enemy[i].unitSetting
		enemy[i].targetUnit = NULL;
	}
}

void SummonUnit(Unit* unit, UnitType type)
{
	// 1. unit 아군인지 적군인지 판단
	// 2. 아군이든 적군이든 인덱스를 찾는다
	// 3. 그 찾은 유닛을 타입에 따라서 초기화 한다.
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
				unit[i].collider.radius = 30;

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 34;
					unit[i].currentHP = 100;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 20;
					unit[i].currentHP = 50;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
				}
				if (allyResource.money - unit[i].price <= 0)
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

		//unit[allyPopulation - 1].type = type;
		//unit[allyPopulation - 1].collider.radius = 30;

		//if (unit[allyPopulation - 1].type == WARRIOR)
		//{
		//	unit[allyPopulation - 1].attackDamage = 34;
		//	unit[allyPopulation - 1].currentHP = 100;
		//	unit[allyPopulation - 1].attackRange.radius = 50;
		//	unit[allyPopulation - 1].price = 10;
		//}
		//else if (unit[allyPopulation - 1].type == ARCHER)
		//{
		//	unit[allyPopulation - 1].attackDamage = 20;
		//	unit[allyPopulation - 1].currentHP = 50;
		//	unit[allyPopulation - 1].attackRange.radius = 300;
		//	unit[allyPopulation - 1].price = 20;
		//}
		//if (allyResource.money - unit[allyPopulation - 1].price <= 0)
		//{
		//	printf("No ally money!!!\n");
		//	return;
		//}
		//allyResource.money -= unit[allyPopulation - 1].price;
		//unit[allyPopulation - 1].alived = TRUE;
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
				unit[i].collider.radius = 30;

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 30;
					unit[i].currentHP = 100;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3;
				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 20;
					unit[i].currentHP = 50;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
					unit[i].attackCoolDown = 2;
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

	/*	if (enemyPopulation < MAX_UNIT)
			enemyPopulation++;*/

		//unit[enemyPopulation - 1].type = type;
		//unit[enemyPopulation - 1].collider.radius = 30;

		//if (unit[enemyPopulation - 1].type == WARRIOR)
		//{
		//	unit[enemyPopulation - 1].attackDamage = 30;
		//	unit[enemyPopulation - 1].currentHP = 100;
		//	unit[enemyPopulation - 1].attackRange.radius = 50;
		//	unit[enemyPopulation - 1].price = 10;
		//	unit[enemyPopulation - 1].attackCoolDown = 3;
		//}
		//else if (unit[enemyPopulation - 1].type == ARCHER)
		//{
		//	unit[enemyPopulation - 1].attackDamage = 20;
		//	unit[enemyPopulation - 1].currentHP = 50;
		//	unit[enemyPopulation - 1].attackRange.radius = 300;
		//	unit[enemyPopulation - 1].price = 20;
		//	unit[enemyPopulation - 1].attackCoolDown = 2;
		//}
		//if (enemyResource.money - unit[enemyPopulation - 1].price <= 0)
		//{
		//	printf("No enemy money!!!\n");
		//	return;
		//}
		//enemyResource.money -= unit[enemyPopulation - 1].price;
		//unit[enemyPopulation - 1].alived = TRUE;
	}
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
		}

		if (enemy[i].alived)
		{
			enemy[i].collider.position = CP_Vector_Set(enemy[i].position.x, enemy[i].position.y);
			enemy[i].attackRange.position = enemy[i].collider.position;
			enemy[i].position.x -= enemy[i].moveSpeed * dt;
		}
	}
}

void DrawUnits(Unit* unit, CP_Image* unitani, int totalframe)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (unit[i].alived)
		{
			if (unit[i].type == WARRIOR)
			{
				if (unit == ally)
				{
					Animation_play(unitani, &unit[i].unitSetting, totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
				}
				else if (unit == enemy)
				{
					Animation_play(unitani, &unit[i].unitSetting, totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
				}
			}
			else if (unit[i].type == ARCHER)
			{

				if (unit == ally)
					Animation_play(unitani, &unit[i].unitSetting, totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
				else if (unit == enemy)
				{
					Animation_play(unitani, &unit[i].unitSetting, totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
				}
			}


		}
	}
}