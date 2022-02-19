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

void PAGE_BT_Audio(void) {
 HAL_GPIO_WritePin(BT_Audio_GPIO_Port, BT_Audio_Pin, GPIO_PIN_SET);

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
	tft.ST7789_Update();
 }
}
