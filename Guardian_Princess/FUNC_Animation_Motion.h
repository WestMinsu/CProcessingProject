#pragma once

typedef struct AnimationFrameInfo
{
	int frameCount;
	int frameSlow;

}AnimationFrameInfo;


CP_Image* Animation_ImageLoader(char foldername[100], int totalframe);
void Animation_play(CP_Image* loaded_file, AnimationFrameInfo*frameSetting, int totalframe, CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA);