#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "asset_loading.h"

CP_Sound Mouse_Click_Sound;// 마우스 클릭 소리
CP_Sound button_sound;// 버튼 소리

CP_Image Cursor_Image; // 커서 이미지

CP_Font Main_TitleFont;// 폰트

//------------------------------------------------

void Sound_load()
{
	Mouse_Click_Sound = CP_Sound_Load("Assets/mouse_settings/test_mouseclick.mp3");
	button_sound = CP_Sound_Load("Assets/main_title_assets/test_button_sound.mp3");
}
void Image_load()
{
	Cursor_Image = CP_Image_Load("Assets/mouse_settings/test_cursor.png");
}
void Font_load()
{
	Main_TitleFont = CP_Font_Load("Assets/fonts/DungGeunMo.ttf");
}