#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//------------------------------------------------



struct testunit_info
{
	int TYPE; //유닛 속성 // 0 - 무속성, 1- 물, 2- 불, 3- 풀

	int HP;  //체력
	int ATK; //공격력
	int DEF; //방어력

	int CRIT_P; //치명타확률
	int CRIT_DMG; //치명타 피해

	float RNG; //공격 사거리 // 0일 경우 근접공격
	float ATK_AREA;// 범위 공격 // 0일 경우 단일 공격

	float ATKSPD; //공격 속도
	float ATKSTART_SPD; //적과 첫 조우시 공격 딜레이
	float MOVSPD; // 이동 속도

	float HITBACK_RNG; //넉백 당할 시, 당하는 정도. 0일 시 넉백 당하지 않음


	float ACC; //명중확률
	float DODGE; //회피확률

	float HPREG; //체력 재생

	int COST; // 생산 비용
	int COST_DTH; // 죽을 시 적에게 주는 비용
	float PRD_TIME;// 생산시간

};