#include "Page.h"

#include "global_define.h"

#include "stdio.h"

#define pColor_0  tft.RGB565(158,158,158)    // ��� �������, ���������
#define pColor_1  tft.RGB565(77,85,74)       // ��� �������� ������ ���
#define pColor_2  tft.RGB565(148,165,142)    // ������� ��� ��������� ������
#define pColor_3  tft.RGB565(208,231,199)    // ������� ����� ��������� ������� ������
#define pColor_4  tft.RGB565(89,99,85)       // ������ ����� ��������� ������� ������
#define pColor_5  tft.RGB565(166,170,165)    // ������� ����� ��������� ������ ������
#define pColor_6  tft.RGB565(46,51,44)       // ������ ����� ��������� ������ ������
#define pColor_7  tft.RGB565(16,16,16)
#define pColor_8  0
#define pColor_9  tft.RGB565(209,209,209)
#define pColor_10 COLOR_DARKCYAN
#define pColor_11 tft.RGB565(255,0,0)
#define pColor_12 tft.RGB565(0,255,0)
#define pColor_13 tft.RGB565(0,0,255)
#define pColor14_WHITE tft.RGB565(255,255,255)    // WHITE
#define pColor15_BLACK tft.RGB565(0,0,0)          // BLACK

uint16_t palitra[256];

void PAGE_init_palitra(void) {
	palitra[0] = pColor_0;
	palitra[1] = pColor_1;
	palitra[2] = pColor_2;
	palitra[3] = pColor_3;
	palitra[4] = pColor_4;
	palitra[5] = pColor_5;
	palitra[6] = pColor_6;
	palitra[7] = pColor_7;
	palitra[8] = pColor_8;
	palitra[9] = pColor_9;
	palitra[10] = pColor_10;
	palitra[11] = pColor_11;
	palitra[12] = pColor_12;
	palitra[13] = pColor_13;
	palitra[14] = pColor14_WHITE;
	palitra[15] = pColor15_BLACK;

	palitra_COLOR_TEXT_DEFAULT = COLOR_TEXT_DEFAULT; //Цвет текста по умолчанию         100
	palitra_COLOR_TEXT_SELECT  = COLOR_TEXT_SELECT;  //Цвет текста выбранной строки     101
	palitra_COLOR_TEXT_DISABLE = COLOR_TEXT_DISABLE;
	palitra_COLOR_RECTAGLE     = COLOR_RECTAGLE;     //Текст выделенной строки         102
	palitra_COLOR_BACKGROUND   = COLOR_BACKGROUND;   // Фон    103

}

void PAGE_Palitra(void) {
	palitra[255] = tft.RGB565(128, 128, 128);
	tft.SetColor(palitra[255]);
	//gfxfont.set_delta_x(2);
	char str[8];
	int start;
	start = 0;
	while (1) {

		KEY.tick();

		if (Encoder.Left) {
			Encoder.Left = 0;
			start -= 16;
			if (start < 0)
				start = 240;
		}

		if (Encoder.Right) {
			Encoder.Right = 0;
			start += 16;
			if (start > 255) {
				start = 0;
			}
		}

		//tft.Fill(palitra[7]);

		int max = 16 + start;
		for (int i = start; i < max; i++) {
			tft.RectangleFilled(60 * (i % 4), 60 * ((i % 16) / 4), 59, 59,
					palitra[i]);
			sprintf(str, "%d", i);
			gfxfont.Puts(60 * (i % 4) + 2, 60 * ((i % 16) / 4) + 22, str);
		}

		if (KEY.isClick())
			return;

		tft.ST7789_Update();
	}

}
