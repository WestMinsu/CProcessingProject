#include "unit.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include "utils.h"
#include <stdio.h>
#include "FUNC_Animation_Motion.h"
Unit ally[MAX_UNIT];
Unit enemy[MAX_UNIT];
int allyPopulation = 0;
int enemyPopulation = 0;



void InitUnit(void)
{
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

		ally[i].unitSetting.frameCount = 0;
		ally[i].unitSetting.frameSlow = 0;
		ally[i].unitSetting.frameSlowRate = 3;

		enemy[i].position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 8.0f);
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
		enemy[i].alived = FALSE;

		enemy[i].unitSetting.frameCount = 0;
		enemy[i].unitSetting.frameSlow = 0;
		enemy[i].unitSetting.frameSlowRate = 6;
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
			unit[allyPopulation - 1].attackDamage = 3;
			unit[allyPopulation - 1].currentHP = 100;
			unit[allyPopulation - 1].attackRange.radius = 50;
			unit[allyPopulation - 1].price = 10;
			unit[allyPopulation - 1].unitSetting.frameCount = 0;

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
		}

		if (enemy[i].alived)
		{
			enemy[i].collider.position = CP_Vector_Set(enemy[i].position.x, enemy[i].position.y);
			enemy[i].attackRange.position = enemy[i].collider.position;
			enemy[i].position.x -= enemy[i].moveSpeed * dt;
		}
	}
}

void DrawUnits(Unit* unit, CP_Image*unitani, int totalframe)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (unit[i].alived)
		{
			if (unit[i].type == WARRIOR)
			{
				if (unit == ally)
				{

					Animation_play(unitani, &unit[i].unitSetting , totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
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
					Animation_play(unitani, &unit[i].unitSetting,totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
				}
			}
		

		}
	}
}