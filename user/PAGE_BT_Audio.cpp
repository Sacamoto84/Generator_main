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
 while (1) {
	KEY.tick();
	if (KEY.isClick()){
		HAL_GPIO_WritePin(BT_Audio_GPIO_Port, BT_Audio_Pin, GPIO_PIN_RESET);
		return;
	}
	tft.ST7789_Update();
 }
}
