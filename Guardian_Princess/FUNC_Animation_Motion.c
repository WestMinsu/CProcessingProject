#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"

//���� �ڵ鸵
static int frame = 0;

CP_Image* Animation_ImageLoader(char foldername[100], int totalframe)//���� �̸��� �� ������ ��(������ ���� �̸�) �Է�
//init �ȿ� ���� ��!!
{
	CP_Image* frame_list = (CP_Image*)malloc(totalframe * sizeof(CP_Image));

	char buffer[100];

	for(int i = 0; i < totalframe; i++) 
	{
		sprintf_s(buffer, 100, "Assets/animation/%s/%d.png", foldername, i);

		frame_list[i] = CP_Image_Load(buffer);
	}
	return frame_list;
}


void Animation_play(CP_Image* loaded_files, AnimationFrameInfo*frameSetting,int totalframe, CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA)
//�ִϸ��̼� ��� �Լ� // update �Լ� �ȿ����� ����� ��
//"asset/animation" ���� ���� �ִ� ���� ��,//������ �ƹ��ų�// �� ������(������ �̹��� ���� ��) / ��� ��ġ �� ũ������ x,y,w,h,���İ� 
{
	// �ִϸ��̼� ���� �ȿ� �ִ� �̹���(loaded files)�� ��ȣ�� ��� ���������� ��� ��, ������ �������� �Ǹ� �ٽ� 0���������� ���ư��� ���� �ݺ�
	// �� �����ӿ� �� �徿 ���
	if (loaded_files == 0)
	{
		return;
	}

	if (totalframe > frameSetting->frameCount)
	{
		CP_Image_Draw(loaded_files[frameSetting->frameCount], aniX, aniY, aniW, aniH, aniA);
		

			if (frameSetting->frameSlow == 2)
			{
				frameSetting->frameCount++;
				frameSetting->frameSlow = 0;
			}
			frameSetting->frameSlow++;
	}	
	else
	{
		if (looping == 1)
		{
			frameSetting->frameCount = 0;
			CP_Image_Draw(loaded_files[frameSetting->frameCount], aniX, aniY, aniW, aniH, aniA);
		}
		else
		{
			return;
		}

	}
}


