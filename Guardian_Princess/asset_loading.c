#include "cprocessing.h"
#include "asset_loading.h"

CP_Sound Mouse_Click_Sound;// 마우스 클릭 소리

CP_Image CursorImage; // 커서 이미지
CP_Sound button_sound;
CP_Font Main_TitleFont;// 폰트

//------------------------------------------------
void SoundLoad()
{
	Mouse_Click_Sound = CP_Sound_Load("Assets/Mouse/test_mouseclick.mp3");
	button_sound = CP_Sound_Load("Assets/MainMenu/test_button_sound.mp3");
}
void ImageLoad()
{
	CursorImage = CP_Image_Load("Assets/Mouse/test_cursor.png");
}
void FontLoad()
{
	Main_TitleFont = CP_Font_Load("Assets/Fonts/DungGeunMo.ttf");
}