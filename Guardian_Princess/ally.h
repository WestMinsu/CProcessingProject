#pragma once
#include "cprocessing.h"
#include "utils.h"




typedef enum
{
	WARRIOR1,
	ARCHER1,
	MAGE
}UnitType; // 유닛이름


typedef struct Ally
{
	CP_Vector position;
	CP_BOOL alived;

	Circle collider; //히트박스
	Circle attackRange;///사거리

	UnitType type; //이름

	int maxHP; //최대체력
	int currentHP;//현재체력

	int attackDamage; //공격
	float attackSpeed;//공속

	int moveSpeed;//이속

	int price; //공격

	int price_death; //죽였을때 받는 돈

	float produceTime; //생산시간
}ALLY;


void SummonAllyUnit(UnitType type);
void UpdateAllyUnits(float dt);
void DrawAllyUnits(void);