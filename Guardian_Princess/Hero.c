#include "hero.h"
#include "colors.h"
#include "utils.h"
#include "unit.h"
#include "enemybase.h"
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"
#include "camera.h"

Hero hero;
extern Unit enemy[MAX_UNIT];
extern EnemyBase enemyBase;

void InitHero()
{
	hero.hero.position = CP_Vector_Set(CP_System_GetWindowWidth() / 5.0f, CP_System_GetWindowHeight() / 4.0f);
	hero.hero.alived = TRUE;
	hero.hero.moveSpeed = 400;
	hero.hero.collider.radius = 120;
	hero.hero.attackRange.position = hero.hero.position;
	hero.hero.attackRange.radius = 50;

	hero.hero.maxHP = 2000;
	hero.hero.currentHP = hero.hero.maxHP;
	hero.hero.attackDamage = 20;
	hero.hero.attackCoolDown = 0.5f;
	hero.hero.targetUnit = NULL;
	hero.hero.attackTimer = 0;
	hero.skillTimer = 0;

	hero.hero.state = IDLE;
	hero.hero.animationFrameInfo.frameCount = 0;
	hero.hero.animationFrameInfo.frameSlow = 0;

	hero.hero.animationStateInfo.Attack.images = heroAttack;
	hero.hero.animationStateInfo.Dead.images = heroDead;
	hero.hero.animationStateInfo.Idle.images = heroIdle;
	hero.hero.animationStateInfo.Walk.images = heroWalk;

	hero.hero.animationStateInfo.Attack.totalframe = 5;
	hero.hero.animationStateInfo.Dead.totalframe = 4;
	hero.hero.animationStateInfo.Idle.totalframe = 5;
	hero.hero.animationStateInfo.Walk.totalframe = 7;

}

extern CP_Vector cameraPos;

void UpdateHero(float dt) //animation walk
{
	if (CP_Input_KeyDown(KEY_A))
	{
		if (hero.hero.position.x > 100)
		{
			hero.hero.state = WALK;
			hero.hero.position.x -= hero.hero.moveSpeed * dt;
			cameraPos.x -= hero.hero.moveSpeed * CP_System_GetDt();
		}
	}

	else if (CP_Input_KeyDown(KEY_D) && !circleToCircle(hero.hero.collider, enemyBase.collider))
	{
		hero.hero.state = WALK;
		hero.hero.position.x += hero.hero.moveSpeed * dt;
		if (cameraPos.x <= CP_System_GetWindowWidth() + 80)
			cameraPos.x += hero.hero.moveSpeed * CP_System_GetDt();
		for (int i = 0; i < MAX_UNIT; i++)
		{
			if (enemy[i].alived && circleToCircle(hero.hero.collider, enemy[i].collider))
			{
				hero.hero.position.x -= hero.hero.moveSpeed * dt;
				cameraPos.x -= hero.hero.moveSpeed * CP_System_GetDt();
			}
		}
	}

	else if(hero.hero.state != ATTACK)
		hero.hero.state = IDLE;

	hero.hero.collider.position = CP_Vector_Set(hero.hero.position.x, hero.hero.position.y);
	hero.hero.attackRange.position = hero.hero.collider.position;
}

void DrawHero()
{
	switch (hero.hero.state)
	{
	case ATTACK:
		Animation_play(hero.hero.animationStateInfo.Attack.images, &hero.hero.animationFrameInfo.frameCount, &hero.hero.animationFrameInfo.frameSlow, hero.hero.animationStateInfo.Attack.totalframe, 1, hero.hero.position.x, hero.hero.position.y, 200, 200, 255);
		break;
	case WALK:
		Animation_play(hero.hero.animationStateInfo.Walk.images, &hero.hero.animationFrameInfo.frameCount, &hero.hero.animationFrameInfo.frameSlow, hero.hero.animationStateInfo.Walk.totalframe, 1, hero.hero.position.x, hero.hero.position.y+50, 200, 200, 255);
		break;
	case DEAD:
		Animation_play(hero.hero.animationStateInfo.Dead.images, &hero.hero.animationFrameInfo.frameCount, &hero.hero.animationFrameInfo.frameSlow, hero.hero.animationStateInfo.Dead.totalframe, 1, hero.hero.position.x, hero.hero.position.y, 200, 200, 255);
		break;
	default:
		Animation_play(hero.hero.animationStateInfo.Idle.images, &hero.hero.animationFrameInfo.frameCount, &hero.hero.animationFrameInfo.frameSlow, hero.hero.animationStateInfo.Idle.totalframe, 1, hero.hero.position.x, hero.hero.position.y, 200, 200, 255);
		break;
	}
}


