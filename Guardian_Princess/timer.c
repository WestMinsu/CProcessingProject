#include <stdio.h>
#include "cprocessing.h"
#include "timer.h"

float get_secs(int s)
{
	float total = 0;

	while( s > total)
	{
		float count_sec = CP_System_GetSeconds() - (CP_System_GetSeconds()-1);
	
		total +=  count_sec;	

	}
	return total;

}