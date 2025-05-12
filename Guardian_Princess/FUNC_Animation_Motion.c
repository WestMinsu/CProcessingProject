#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cprocessing.h"
#include "FUNC_Animation_Motion.h"
#include "unit.h"

//¿¡·¯ ÇÚµé¸µ
static int frame = 0;

CP_Image* Animation_ImageLoader(char foldername[100], int totalframe)//Æú´õ ÀÌ¸§°ú ÃÑ ÇÁ·¹ÀÓ ¼ö(¸¶Áö¸· Æú´õ ÀÌ¸§) ÀÔ·Â
//init ¾È¿¡ ³ÖÀ» °Í!!
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


<<<<<<< Updated upstream
void Animation_play(CP_Image* loaded_files, AnimationFrameInfo*frameSetting,int totalframe,CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA)
//¾Ö´Ï¸ÞÀÌ¼Ç Àç»ý ÇÔ¼ö // update ÇÔ¼ö ¾È¿¡¼­¸¸ »ç¿ëÇÒ °Í
//"asset/animation" Æú´õ ³»¿¡ ÀÖ´Â Æú´õ ¸í,//º¯¼ö¸í ¾Æ¹«°Å³ª// ÃÑ ÇÁ·¹ÀÓ(¸¶Áö¸· ÀÌ¹ÌÁö ÆÄÀÏ ¸í) / Àç»ý À§Ä¡ ¹× Å©±âÁ¤º¸ x,y,w,h,¾ËÆÄ°ª 
=======
void Animation_play(CP_Image* loaded_files, int* framecount ,int* frameslow,int totalframe, CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA)
//ï¿½Ö´Ï¸ï¿½ï¿½Ì¼ï¿½ ï¿½ï¿½ï¿½ ï¿½Ô¼ï¿½ // update ï¿½Ô¼ï¿½ ï¿½È¿ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
//"asset/animation" ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½,//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Æ¹ï¿½ï¿½Å³ï¿½// ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ì¹ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½) / ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡ ï¿½ï¿½ Å©ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ x,y,w,h,ï¿½ï¿½ï¿½Ä°ï¿½ 
>>>>>>> Stashed changes
{
	// ¾Ö´Ï¸ÞÀÌ¼Ç Æú´õ ¾È¿¡ ÀÖ´Â ÀÌ¹ÌÁö(loaded files)¸¦ ¹øÈ£¼ø ´ë·Î ¼øÂ÷ÀûÀ¸·Î Àç»ý ÈÄ, ¸¶Áö¸· ÇÁ·¹ÀÓÀÌ µÇ¸é ´Ù½Ã 0ÇÁ·¹ÀÓÀ¸·Î µ¹¾Æ°¡´Â °ÍÀ» ¹Ýº¹
	// ÇÑ ÇÁ·¹ÀÓ¿¡ ÇÑ Àå¾¿ Àç»ý
	if (loaded_files == 0)
	{
		return;
	}

	if (totalframe > *framecount)
	{
		CP_Image_Draw(loaded_files[*framecount], aniX, aniY, aniW, aniH, aniA);
		

<<<<<<< Updated upstream
			if (frameSetting->frameSlow == frameSetting->frameSlowRate)
=======
			if (*frameslow == 4)
>>>>>>> Stashed changes
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


