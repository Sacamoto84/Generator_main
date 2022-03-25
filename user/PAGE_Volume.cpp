#include "Page.h"
#include "global_define.h"
#include "stdio.h"

#include "TFTWiget.h"

TFT_Wiget_Animated_Button B, B1, B2;

void PAGE_Volume(void)
{
	int i = 0;

	B.init_tft(&tft);
    B.setHW(32, 200);

    B1.init_tft(&tft);
    B1.setHW(32, 200);
    B1.setY(40);

    B2.init_tft(&tft);
    B2.setHW(32, 200);
    B2.setY(80);

    SEGGER_RTT_WriteString(0, "Wiget\n");

	while (1) {
		KEY.tick();

		if (Encoder.Left) {
			Encoder.Left = 0;
			i+=1;
			if (i>2) i=2;

			if (i == 0){
				B.select(1);
               B1.select(0);
               B2.select(0);
		}

			if (i == 1){
						B.select(0);
		               B1.select(1);
		               B2.select(0);
				}

			if (i == 2){
						B.select(0);
		               B1.select(0);
		               B2.select(1);
				}


		}

		if (Encoder.Right) {
			Encoder.Right = 0;
			i-=1;
			if(i<0) i=0;

			if (i == 0){
				B.select(1);
               B1.select(0);
               B2.select(0);
		}

			if (i == 1){
						B.select(0);
		               B1.select(1);
		               B2.select(0);
				}

			if (i == 2){
						B.select(0);
		               B1.select(0);
		               B2.select(1);
				}

		}





		tft.Fill(COLOR_DARKBLUE);
		tft.Font_Smooth_drawStr(30, 30, "Wiget");



        B.run();
        B1.run();
        B2.run();
        //tft.ST7789_Update(B.info());



		tft.ST7789_UpdateDMA16bitV3();

	    if (KEY.isClick())
					return;	
		}
}
