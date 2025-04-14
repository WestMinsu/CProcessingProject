
#include "cprocessing.h"
#include "unit_info.h" //유닛 정보
#include "testroom.h" // 실험 페이지
#include "asset_loading.h" //에셋 불러오기는 여기서
#include "intro_scene.h"
#include "title_scene.h"
#include "timer.h"

//------------------------내장 함수 불러오기-------------------------

CP_BOOL cursor = FALSE; // 커서 보이기 유무 설정

//-------------------함수 추가 선언 -----------------------------

////마우스 커서 작동

	void cursor_sound(float input_x1, float input_y1, float input_w1, float input_h1)
	{	

		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		{
			if ((((CP_Input_GetMouseX() <= (input_x1 + (input_w1 * 0.5))) && (CP_Input_GetMouseX() >= (input_x1 - (input_w1 * 0.5)))) && ((CP_Input_GetMouseY() <= (input_y1 + (input_h1 * 0.5))) && (CP_Input_GetMouseY() >= (input_y1 - (input_h1 * 0.5))))))
			{

				CP_Sound_Play(button_sound);
				CP_Engine_SetNextGameState(testroom_init, testroom_update, testroom_exit);
			}
			else
			{
				CP_Sound_Play(Mouse_Click_Sound);

			}
		}
	
	}

	




void game_init(void)
{
	// --------------------------------에셋 불러오기 --------------
	sound_load();
	image_load();
	font_load();

	// --------------인트로 불러오기 -------------

	//CP_Engine_SetNextGameState(intro_init, intro_update, intro_exit);



	CP_System_SetWindowTitle("Guardian Princess\n"); //프로그램 창 이름
	CP_System_ShowCursor(cursor);//커서 보이게 하기
	
	//-----------------------------음악 설정------------------------------

	CP_Sound_Play(Main_Title_Music);

	
}

float elapsed_time = 0;

void game_update(void)
{
	elapsed_time += CP_System_GetDt();
	if (elapsed_time >= 15)
	{
		printf("done!\n");
	}

	printf("t: %f\n", elapsed_time);

	//------------------------------이미지 재생-----------------------------
		// 메인 배경 이미지
	float x = (float)CP_System_GetWindowWidth() / 2;
	float y = (float)CP_System_GetWindowHeight() / 2;
	float w = (float)CP_System_GetWindowWidth();
	float h = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(Main_Title_Image, x, y, w, h, 255);

	// 버튼 이미지

	CP_Image_Draw(button_test, 50, 50, 50, 50, 255);
	cursor_sound(50, 50, 50, 50);

	// 커서 이미지

	CP_Image_Draw(Cursor_image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 30, 30, 255);

}


void game_exit(void)
{
	//------------------------------이미지, 음악 종료---------------------------
	CP_Image_Free(&Main_Title_Image);
	CP_Sound_Free(&Main_Title_Music);
}


int main(void)
{
	//----------------------------윈도우 사이즈 크기 조절---------------------------
	CP_System_SetWindowSize(1600, 800);


	//-------------------------------------------------------------------
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	
	return 0;
}
