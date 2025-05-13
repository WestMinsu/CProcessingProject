#pragma once
typedef struct AnimationFrameInfo
{
	int frameCount;
	int frameSlow;
}AnimationFrameInfo; //À¯´ÖÇÏ³ª¾¿

typedef struct AnimationDrawInfo
{
	CP_Image* images;
	int totalframe;
}AnimationDrawInfo;

typedef struct AnimationState
{
	AnimationDrawInfo Attack;
	AnimationDrawInfo Dead;
	AnimationDrawInfo Idle;
	AnimationDrawInfo Walk;


}AnimationState;



CP_Image* Animation_ImageLoader(char foldername[100], int totalframe);
void Animation_play(CP_Image* loaded_file, int* framecount, int* frameslow, int totalframe, CP_BOOL looping, float aniX, float aniY, float aniW, float aniH, int aniA);