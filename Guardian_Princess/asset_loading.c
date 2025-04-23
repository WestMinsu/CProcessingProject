#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "asset_loading.h"

CP_Sound Mouse_Click_Sound;// 마우스 클릭 소리
CP_Sound button_sound;// 버튼 소리

CP_Image Main_Title_Image; //메인 타이틀 이미지
CP_Image Cursor_Image; // 커서 이미지
CP_Image button_start;// 버튼 이미지
CP_Image button_exit;

CP_Image Intro_digipen; //디지펜 로고
CP_Image Intro_teamlogo;//팀 로고 출력
CP_Image Intro_bic;//bic 로고 출력

CP_Font mainTitleFont;// 폰트


CP_Image button_start;// 테스트 버튼
CP_Image button_exit;
//------------------------------------------------

void sound_load()
{
	Mouse_Click_Sound = CP_Sound_Load("Assets/mouse_settings/test_mouseclick.mp3");
	button_sound = CP_Sound_Load("Assets/main_title_assets/test_button_sound.mp3");
}

//------------------------------------------------

void image_load()
{
	Main_Title_Image = CP_Image_Load("Assets/main_title_assets/download.png");
	button_start = CP_Image_Load("Assets/main_title_assets/start.png");
	button_exit = CP_Image_Load("Assets/main_title_assets/exit.png");
	Cursor_Image = CP_Image_Load("Assets/mouse_settings/test_cursor.png");

	Intro_bic = CP_Image_Load("Assets/intro_assets/bic_logo.png");
	Intro_digipen = CP_Image_Load("Assets/intro_assets/digipen_logo.png");
	Intro_teamlogo = CP_Image_Load("Assets/intro_assets/frostbyte_logo.png");
}

//------------------------------------------------

void font_load()
{
	mainTitleFont = CP_Font_Load("Assets/fonts/DungGeunMo.ttf");
}