#include "ally.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include <stdio.h>
extern Ally ally[MAX_UNIT];
extern AllyResource allyResource;

void SummonAllyUnit(UnitType type)
{
	static int idx = 0;

	if (idx >= MAX_UNIT)
	{
		printf("Can't summon ally unit!!!\n");

		return;
	}

	if (allyResource.money - ally[idx].price <= 0)
	{
		printf("No money!!!\n");
		return;
	}

	ally[idx].collider.radius = 30;
	ally[idx].attackRange.radius = 50;
	ally[idx].type = type;

	if (ally[idx].type == RANGED)
	{
		ally[idx].attackRange.radius = 200;
		ally[idx].price = 50;
	}

	allyResource.money -= ally[idx].price;
	ally[idx].alived = TRUE;
	idx++;
}

void UpdateAllyUnits(float dt)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived)
		{
			ally[i].collider.position = CP_Vector_Set(ally[i].position.x, ally[i].position.y);
			ally[i].attackRange.position = ally[i].collider.position;
			ally[i].position.x += ally[i].moveSpeed * dt;
		}
	}
}

void DrawAllyUnits(void)
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived)
		{
			if (ally[i].type == MELEE)
			{
				CP_Settings_Fill(blue);
			}
			else if (ally[i].type == RANGED)
			{
				CP_Settings_Fill(pink);
			}
			CP_Graphics_DrawCircle(ally[i].position.x, ally[i].position.y, 30);
		}
	}
}