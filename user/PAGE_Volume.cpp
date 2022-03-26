#include <TFT_Wiget_Animated_Rectagle.h>
#include "Page.h"
#include "global_define.h"
#include "stdio.h"
#include "TFT_gif.h"


TFT_gif gif;

void PAGE_Volume(void)
{
	int i = 0;

    SEGGER_RTT_WriteString(0, "Wiget\n");

    TFT_gif gif;
    gif.init(&tft);
    gif.setName((char *)"Q1");
    gif.setMaxIndex(23);
    gif.setDelay(0);
    gif.useAplpha(1);
    gif.setSwap(0);
    gif.SetXY(10, 10);
    gif.setOffset(4*21);
    gif.trigger = HOVER;

    TFT_gif gif2;
    gif2.init(&tft);
    gif2.setName((char *)"Q1");
    gif2.setMaxIndex(23);
    gif2.setDelay(0);
    gif2.useAplpha(1);
    gif2.setSwap(0);
    gif2.SetXY(100, 10);
    gif2.setOffset(4*21);
    gif2.trigger = LOOP;


    TFT_gif gif3;
    gif3.init(&tft);
    gif3.setName((char *)"Q1");
    gif3.setMaxIndex(23);
    gif3.setDelay(0);
    gif3.useAplpha(1);
    gif3.setSwap(0);
    gif3.SetXY(10, 150);
    gif3.setOffset(4*21);
    gif3.trigger = MORPH;

    TFT_gif gif4;
    gif4.init(&tft);
    gif4.setName((char *)"Q1");
    gif4.setMaxIndex(23);
    gif4.setDelay(0);
    gif4.useAplpha(1);
    gif4.setSwap(0);
    gif4.SetXY(100, 150);
    gif4.setOffset(4*21);
    gif4.trigger = BOOMERANG;



	while (1) {
		KEY.tick();

		if (Encoder.Left) {
			Encoder.Left = 0;
			i+=1;
			if (i>2) i=2;

			gif .command(cSTOP);
			gif2.command(cSTOP);
			gif3.command(cSTOP);
			gif4.command(cSTOP);

		}

		if (Encoder.Right) {
			Encoder.Right = 0;
			i-=1;
			if(i<0) i=0;

			gif .command(cPLAY);
			gif2.command(cPLAY);
			gif3.command(cPLAY);
			gif4.command(cPLAY);
		}

		tft.Fill(COLOR_DARKBLUE);
		//tft.Font_Smooth_drawStr(30, 30, "Wiget");


		gif.run();
		gif2.run();
		gif3.run();
		gif4.run();

		//tft.ST7789_Update(gif.info());
		//tft.ST7789_Update(gif2.info());
		//tft.ST7789_Update(gif3.info());
		//tft.ST7789_Update(gif4.info());








		tft.ST7789_UpdateDMA16bitV3();

	    if (KEY.isClick())
					return;	
		}
}
