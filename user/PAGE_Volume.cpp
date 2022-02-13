#include "Page.h"
#include "global_define.h"
#include "stdio.h"

extern Bitmap bmpBackground240240;

extern Bitmap bmp_on_3232;
extern Bitmap bmp_off_3232;

void PAGE_Volume(void)
{
	while (1) {
		KEY.tick();
	

	
	    if (KEY.isClick())
					return;	
		}
}
