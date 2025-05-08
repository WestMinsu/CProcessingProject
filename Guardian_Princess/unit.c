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
CP_Vector allyPosition; // why ����?? why do you love ���� ���� so much??? 
CP_Vector enemyPosition;

void InitUnit()
{
	allyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 4.0f);
	enemyPosition = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f * 4.0f, CP_System_GetWindowHeight() / 4.0f);
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
		ally[i].attackCoolDown = 1;
		ally[i].price = 1;
		//ally[i].unitSetting ???
		ally[i].targetUnit = NULL;
		ally[i].attackTimer = 0;

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
		// enemy[i].unitSetting
		enemy[i].targetUnit = NULL;
		enemy[i].attackTimer = 0;
	}
}

void SummonUnit(Unit* unit, UnitType type, AnimationDesc desc)
{
	// 1. unit �Ʊ����� �������� �Ǵ�
	// 2. �Ʊ��̵� �����̵� �ε����� ã�´�
	// 3. �� ã�� ������ Ÿ�Կ� ���� �ʱ�ȭ �Ѵ�.
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
				unit[i].unitSetting.images = desc.images;
				unit[i].unitSetting.totalframe = desc.totalframe;
				unit[i].collider.position = unit[i].position;
				unit[i].collider.radius = 30;
				unit[i].targetUnit = NULL;
				printf("hi\n");

				if (unit[i].type == WARRIOR)
				{
					printf("warrior\n");

					unit[i].attackDamage = 33;
					unit[i].currentHP = 100;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; //TODO: 0.5f�� ù ��° ���� ���� �ð����� ����
				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 20;
					unit[i].currentHP = 50;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
					unit[i].attackCoolDown = 2.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; //TODO: 0.5f�� ù ��° ���� ���� �ð����� ����
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
				unit[i].unitSetting.images = desc.images;
				unit[i].unitSetting.totalframe = desc.totalframe;
				unit[i].collider.position = unit[i].position;
				unit[i].collider.radius = 30;
				unit[i].targetUnit = NULL;
				unit[i].attackTimer = 3.0f;

				if (unit[i].type == WARRIOR)
				{
					unit[i].attackDamage = 34;
					unit[i].currentHP = 100;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 50;
					unit[i].price = 10;
					unit[i].attackCoolDown = 3.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; //TODO: 0.5f�� ù ��° ���� ���� �ð����� ����
				}
				else if (unit[i].type == ARCHER)
				{
					unit[i].attackDamage = 21;
					unit[i].currentHP = 50;
					unit[i].attackRange.position = unit[i].collider.position;
					unit[i].attackRange.radius = 300;
					unit[i].price = 20;
					unit[i].attackCoolDown = 2.0f;
					unit[i].attackTimer = unit[i].attackCoolDown - 0.5f; //TODO: 0.5f�� ù ��° ���� ���� �ð����� ����
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

void DrawUnits(Unit* unit, int totalframe)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (unit[i].alived)
		{
			if (unit[i].type == WARRIOR)
			{
				if (unit == ally)
				{
					Animation_play(unit[i].unitSetting.images, &unit[i].unitSetting, unit[i].unitSetting.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
				}
				else if (unit == enemy)
				{
					Animation_play(unit[i].unitSetting.images, &unit[i].unitSetting, unit[i].unitSetting.totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
				}
			}
			else if (unit[i].type == ARCHER)
			{
				if (unit == ally)
					Animation_play(unit[i].unitSetting.images, &unit[i].unitSetting, unit[i].unitSetting.totalframe, 1, unit[i].position.x, unit[i].position.y, 128, 128, 255);
				else if (unit == enemy)
				{
					Animation_play(unit[i].unitSetting.images, &unit[i].unitSetting, unit[i].unitSetting.totalframe, 1, unit[i].position.x, unit[i].position.y, -256, 256, 255);
				}
			}
		}
	}
}