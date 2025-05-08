#include "ally.h"
#include "constants.h"
#include "colors.h"
#include "resource.h"
#include <stdio.h>
extern ALLY ally[MAX_UNIT];
extern AllyResource allyResource;



void SummonAllyUnit(UnitType type)
{
	static int idx = 0;

	//�ִ� ���� ����
	if (idx >= MAX_UNIT)
	{
		printf("Can't summon ally unit!!!\n");

		return;
	}

	ally[idx].type = type;

	//--------------------------���� ���� �� Ÿ�Ը��� ����
	if (ally[idx].type == WARRIOR)
	{	
		ally[idx].collider.radius = 30;
		ally[idx].attackRange.radius = 10;
		ally[idx].price = 50;
	} 
	else if (ally[idx].type == ARCHER)
	{
		ally[idx].attackRange.radius = 200;
		ally[idx].price = 50;
	}
	else if (ally[idx].type == MAGE)
	{
		ally[idx].attackRange.radius = 100;
		ally[idx].price = 50;
	}

	// ���� ��ȯ�� �� �輱 

	if (allyResource.money - ally[idx].price <= 0)
	{
		printf("No money!!!\n");
		return;
	} 
	allyResource.money -= ally[idx].price;
	ally[idx].alived = TRUE;
	idx++;

}

void UpdateAllyUnits(float dt) //���� �̵�
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



void DrawAllyUnits(void) //���� �׸���
{
	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (ally[i].alived)
		{
			if (ally[i].type == WARRIOR)
			{
				CP_Settings_Fill(blue);
			}
			else if (ally[i].type == ARCHER)
			{
				CP_Settings_Fill(pink);
			}
			CP_Graphics_DrawCircle(ally[i].position.x, ally[i].position.y, 30);
		}
	}
}