#include "cprocessing.h"
#include "utils.h"
#include "game.h"


CP_BOOL timeElapsed(EnemySpawner* enemySpawner, float time, UnitType type)
{
	float dt = 0;
	dt = CP_System_GetDt();

	enemySpawner[type].timer += dt;
	if (enemySpawner[type].timer >= time)
	{
		enemySpawner[type].timer = 0;
		return TRUE;
	}
	else
		return FALSE;
}

CP_BOOL circleToCircle(Circle a, Circle b)
{
	if (a.radius <= 0 || b.radius <= 0)
		return FALSE;
	CP_Vector n = CP_Vector_Set(b.position.x - a.position.x, b.position.y - a.position.y);
	double r = a.radius + b.radius;
	double d = n.x * n.x + n.y * n.y; 
	if (r > 0 && d <= r * r) return TRUE;
	return FALSE;
}