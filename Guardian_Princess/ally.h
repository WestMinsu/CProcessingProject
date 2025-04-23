#pragma once
#include "cprocessing.h"
#include "utils.h"




typedef enum
{
	WARRIOR1,
	ARCHER1,
	MAGE
}UnitType; // �����̸�


typedef struct Ally
{
	CP_Vector position;
	CP_BOOL alived;

	Circle collider; //��Ʈ�ڽ�
	Circle attackRange;///��Ÿ�

	UnitType type; //�̸�

	int maxHP; //�ִ�ü��
	int currentHP;//����ü��

	int attackDamage; //����
	float attackSpeed;//����

	int moveSpeed;//�̼�

	int price; //����

	int price_death; //�׿����� �޴� ��

	float produceTime; //����ð�
}ALLY;


void SummonAllyUnit(UnitType type);
void UpdateAllyUnits(float dt);
void DrawAllyUnits(void);