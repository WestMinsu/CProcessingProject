#include "camera.h"

CP_Matrix GetCameraMatrix(CP_Vector position, float zoom)
{
	CP_Vector screenCenter = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);

	CP_Matrix scale = CP_Matrix_Scale(CP_Vector_Set(zoom, zoom));

	CP_Matrix translate = CP_Matrix_Translate(CP_Vector_Negate(position));

	CP_Matrix moveToScreenCenter = CP_Matrix_Translate(screenCenter);

	return CP_Matrix_Multiply(moveToScreenCenter, CP_Matrix_Multiply(scale, translate));
}


