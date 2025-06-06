﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"
#include "unit.h"



CP_Image* Animation_ImageLoader(char foldername[100], int totalframe)//폴더 이름과 총 프레임 수(마지막 폴더 이름) 입력
//init 안에 넣을 것!!
{
	CP_Image* frame_list = (CP_Image*)malloc(totalframe * sizeof(CP_Image));

	char buffer[100];

	for (int i = 0; i < totalframe; i++)
	{
		sprintf_s(buffer, 100, "Assets/animation/%s/%d.png", foldername, i);

		frame_list[i] = CP_Image_Load(buffer);
	}
	return frame_list;
}


void Animation_play(CP_Image* loaded_files, int* framecount, int* frameslow, int totalframe, CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA)
{

	if (loaded_files == 0)
	{
		return;
	}

	if (totalframe > *framecount)
	{
		CP_Image_Draw(loaded_files[*framecount], aniX, aniY, aniW, aniH, aniA);

		if (*frameslow == 5)
		{
			(*framecount)++;
			*frameslow = 0;
		}
		(*frameslow)++;
	}
	else
	{
		if (looping == 1)
		{
			*framecount = 0;
			CP_Image_Draw(loaded_files[*framecount], aniX, aniY, aniW, aniH, aniA);
		}
		else
		{
			return;
		}

	}
}


