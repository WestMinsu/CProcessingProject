#pragma once





extern CP_Sound Mouse_Click_Sound;// 클릭 소리
extern CP_Sound button_sound;// 버튼 소리 

//-----------------------------------------------

extern CP_Image Main_Title_Image; //메인 타이틀 이미지
extern CP_Image Cursor_image; // 커서 이미지
extern CP_Image button_test;//  버튼 이미지

//------------------------------------------------

extern CP_Image Intro_digipen; //디지펜 로고
extern CP_Image Intro_teamlogo;//팀 로고 출력
extern CP_Image Intro_bic;//bic 로고 출력

extern CP_Font Main_Title_font;// 폰트

//------------------------------------------------


extern CP_Image button_start;// 테스트 버튼
extern CP_Image button_exit;
//------------------------------------------------

void sound_load();
void image_load();
void font_load();