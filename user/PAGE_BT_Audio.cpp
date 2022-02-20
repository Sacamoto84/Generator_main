/*
 * PAGE_BT_Audio.cpp
 *
 *  Created on: 15 февр. 2022 г.
 *      Author: Ivan
 */

#include "Page.h"
#include "global_define.h"
#include "stdio.h"
#include "main.h"

#include "TFT_gif.h"




void PAGE_BT_Audio(void) {
 HAL_GPIO_WritePin(BT_Audio_GPIO_Port, BT_Audio_Pin, GPIO_PIN_SET);

 TFT_gif gif;
 gif.init(&tft);
 gif.setName("BT");
 gif.setMaxIndex(44);
 gif.setDelay(0);
 gif.useAplpha(1);
 gif.setSwap(0);

 TFT_gif gif2;
 gif2.init(&tft);
 gif2.setName("Q1");
 gif2.setMaxIndex(23);
 gif2.setDelay(0);
 gif2.useAplpha(1);
 gif2.setSwap(0);
 gif2.SetXY(120, 120);
 gif2.setOffset(4*21);






 Gen.pause(); //Останавливаем таймер6


 //sprintf(str, "%d", i);
 tft.Fill(BLUE);
 tft.Font_Smooth_Load(&_acRoboto_Medium_en_ru_30[0]);
 tft.Font_Smooth_drawStr(30, 100, "BT Audio");

 //gfxfont.Puts(10, 22, "USB Audio");

 while (1) {
	KEY.tick();
	if (KEY.isClick()){
		HAL_GPIO_WritePin(BT_Audio_GPIO_Port, BT_Audio_Pin, GPIO_PIN_RESET);
		return;
	}

   tft.Fill(BLUE);

   gif.run();
   gif2.run();

   tft.ST7789_Update(gif.info());
   tft.ST7789_Update(gif2.info());
 }
}
