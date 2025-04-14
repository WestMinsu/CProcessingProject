#include <stdio.h>
#include "cprocessing.h"
#include "unit_info.h"
#include "asset_loading.h"

CP_Image Cursor_image; 

void testroom_init(void)
{
	  CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	  Cursor_image = CP_Image_Load("Assets/mouse_settings/test_cursor.png");
}

void testroom_update(void)

{
	CP_Image_Draw(Cursor_image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 30, 30, 255);
}

void testroom_exit(void)

{
}
