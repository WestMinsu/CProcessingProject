#pragma once
#include <stdio.h>
#include "cprocessing.h"


extern CP_Sound Main_Title_Music;// Ÿ��Ʋ ���� 
extern CP_Sound Mouse_Click_Sound;// Ŭ�� �Ҹ�
extern CP_Sound button_sound;// ��ư �Ҹ� 

//-----------------------------------------------

extern CP_Image Main_Title_Image; //���� Ÿ��Ʋ �̹���
extern CP_Image Cursor_Image; // Ŀ�� �̹���
extern CP_Image button_test;//  ��ư �̹���

extern CP_Image button_start;// �׽�Ʈ ��ư
extern CP_Image button_exit;

//------------------------------------------------

extern CP_Image Intro_digipen; //������ �ΰ�
extern CP_Image Intro_teamlogo;//�� �ΰ� ���
extern CP_Image Intro_bic;//bic �ΰ� ���

extern CP_Font Main_Title_font;// ��Ʈ

//------------------------------------------------

void sound_load();
void image_load();
void font_load();