#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"

CP_Image* Animation_ImageLoader(char foldername[100], int totalframe)//���� �̸��� �� ������ ��(������ ���� �̸�) �Է�
//init �ȿ� ���� ��!!
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
//�ִϸ��̼� ��� �Լ� // update �Լ� �ȿ����� ����� ��
//"asset/animation" ���� ���� �ִ� ���� ��, �� ������(������ �̹��� ���� ��) / ��� ��ġ �� ũ������ x,y,w,h,���İ�
{
	// �ִϸ��̼� ���� �ȿ� �ִ� �̹���(loaded files)�� ��ȣ�� ��� ���������� ��� ��, ������ �������� �Ǹ� �ٽ� 0���������� ���ư��� ���� �ݺ�
	// �� �����ӿ� �� �徿 ���

	static int frame_count = 0;
	static int frame_slow = 0;

	// Todo: �� �����ϴ��� ����
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


