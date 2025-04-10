
#include "cprocessing.h"

//------------------------내장 함수 불러오기-------------------------

CP_Image Main_Title_Image; //메인 이미지 재생
CP_Image Cursor_image; // 커서 이미지
CP_Image button_test;// 테스트 버튼

CP_Sound Main_Title_Music;// 메인 음악 재생
CP_Sound Mouse_Click_Sound;// 마우스 클릭 음악 재생
CP_Sound button_sound;//

CP_Font Main_Title_font;// 메인 폰트 변경

CP_BOOL cursor = FALSE; // 커서 보이기 유무 설정


//-------------------함수 추가 선언 -----------------------------

		//마우스 커서 작동
void cursor_sound(float input_x1, float input_y1, float input_w1, float input_h1)
{	

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		if ((((CP_Input_GetMouseX() <= (input_x1 + (input_w1 * 0.5))) && (CP_Input_GetMouseX() >= (input_x1 - (input_w1 * 0.5)))) && ((CP_Input_GetMouseY() <= (input_y1 + (input_h1 * 0.5))) && (CP_Input_GetMouseY() >= (input_y1 - (input_h1 * 0.5))))))
		{

			CP_Sound_Play(button_sound);
		}
		else
		{
			CP_Sound_Play(Mouse_Click_Sound);

		}
	}
	
}




				

//--------------------작동 여부 확인 트리거-----------------------------







void game_init(void)
{
	CP_System_SetWindowTitle("Guardian Princess\n"); //프로그램 창 이름
	CP_System_ShowCursor(cursor);//커서 보이게 하기

	//--------------------------에셋 정의 및 로딩---------------------------

	Main_Title_Image = CP_Image_Load("Assets/main_title_assets/download.png");
	Main_Title_Music = CP_Sound_Load("Assets/main_title_assets/main_ost.mp3");
	Main_Title_font = CP_Font_Load("Assets/fonts/DungGeunMo.ttf");
	button_test = CP_Image_Load("Assets/main_title_assets/start.png");
	Cursor_image = CP_Image_Load("Assets/mouse_settings/test_cursor.png");
	Mouse_Click_Sound = CP_Sound_Load("Assets/mouse_settings/test_mouseclick.mp3");
	button_sound = CP_Sound_Load("Assets/main_title_assets/test_button_sound.mp3");

	//-----------------------------음악 설정------------------------------

	CP_Sound_Play(Main_Title_Music);

	
}


void game_update(void)
{

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



	//--------------------------마우스 클릭 관련 설정-----------------------------



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
