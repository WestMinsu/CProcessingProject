#include "ally.h"
#include "constants.h"
#include "colors.h"
#include <stdio.h>
extern Ally ally[MAX_UNIT];
extern float dt;

void SummonAllyUnit(UnitType type)
{
	static int idx = 0;

	if (idx >= MAX_UNIT)
	{
		printf("Can't summon ally unit!!!\n");

		return;
	}

	ally[idx].collider.radius = 30;
	ally[idx].attackRange.radius = 50;
	ally[idx].type = type;

	if (ally[idx].type == RANGED)
	{
		ally[idx].attackRange.radius = 200;
	}

	ally[idx].alived = TRUE;
	idx++;
}

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