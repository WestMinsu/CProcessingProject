#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"

CP_Image* Animation_ImageLoader(char foldername[100], int totalframe)//폴더 이름과 총 프레임 수(마지막 폴더 이름) 입력
//init 안에 넣을 것!!
{
	CP_Image* frame_list = (CP_Image*)malloc(totalframe * sizeof(CP_Image));

	for(int i = 0; i < totalframe; i++) 
	{
		char buffer[100];

		sprintf_s(buffer, 100, "Assets/animation/%s/%d.png", foldername, i);

		frame_list[i] = CP_Image_Load(buffer);

	}

	return frame_list;
}



void Animation_play(CP_Image* loaded_files, int totalframe, CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA)
//애니메이션 재생 함수 // update 함수 안에서만 사용할 것
//"asset/animation" 폴더 내에 있는 폴더 명, 총 프레임(마지막 이미지 파일 명) / 재생 위치 및 크기정보 x,y,w,h,알파값
{
	// 애니메이션 폴더 안에 있는 이미지(loaded files)를 번호순 대로 순차적으로 재생 후, 마지막 프레임이 되면 다시 0프레임으로 돌아가는 것을 반복
	// 한 프레임에 한 장씩 재생

	static int frame_count = 0;
	static int frame_slow = 0;

	// Todo: 왜 리턴하는지 설명
	if (loaded_files == 0)
	{
		return;
	}

	if (frame_slow == 2)
	{
		if (totalframe != frame_count + 1)
		{
			CP_Image_Draw(loaded_files[frame_count], aniX, aniY, aniW, aniH, aniA);
			frame_count++;
		}
		else
		{
			if (looping == 1)
			{
				frame_count = 0;
				CP_Image_Draw(loaded_files[frame_count], aniX, aniY, aniW, aniH, aniA);
				frame_count++;
			}

		}
		frame_slow = 0;
		frame_slow++;
	}
	else
	{
		frame_slow++;

	}
}


