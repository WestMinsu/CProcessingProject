#include "enemy.h"
#include "constants.h"
#include "colors.h"
#include <stdio.h>

extern Enemy enemy[MAX_UNIT];

void SummonEnemyUnit(UnitType type)
{
	static int idx = 0;

	if (idx >= MAX_UNIT)
	{
		printf("Can't summon enemy unit!!!\n");
		return;
	}

	enemy[idx].collider.radius = 30;
	enemy[idx].attackRange.radius = 50;
	enemy[idx].type = type;

	if (enemy[idx].type == ARCHER)
	{
		enemy[idx].attackRange.radius = 200;
	}

	enemy[idx].alived = TRUE;

	idx++;
}

void UpdateEnemyUnits(float dt)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (enemy[i].alived)
		{
			enemy[i].collider.position = CP_Vector_Set(enemy[i].position.x, enemy[i].position.y);
			enemy[i].attackRange.position = enemy[i].collider.position;
			enemy[i].position.x -= enemy[i].moveSpeed * dt;
		}
	}
}

void DrawEnemyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (enemy[i].alived)
		{
			if (enemy[i].type == WARRIOR)
			{
				CP_Settings_Fill(red);
			}
			else if (enemy[i].type == ARCHER)
			{
				CP_Settings_Fill(white);
			}

			CP_Graphics_DrawCircle(enemy[i].position.x, enemy[i].position.y, 30);
		}
	}
}