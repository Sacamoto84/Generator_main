#include "Page.h"
//#include "global_define.h"
#include "stdio.h"

void PAGE_Font(void)
{
	while(1)
	{
		KEY.tick();
		tft.Fill16(COLOR_BACKGROUND);

		if (KEY.isRelease())
					return;

				tft.ST7789_UpdateDMA16bitV2();

	}
}
