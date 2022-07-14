#include "Page.h"

#include "global_define.h"
#include "stdio.h"

#include "mString.h"

typedef struct {
	char text[20];
} item_files;

void PAGE_Script(void) {
	char str[32];
	static FRESULT res;
	DIR dir;
	FILINFO fno;

	mString<20> sFiles[32];
	int countFiles = 1;

	sFiles[0] = "<-Back";

	res = f_opendir(&dir, (char*) "/script"); /* Open the directory */
	if (res == FR_OK) {
		for (;;) {
			res = f_readdir(&dir, &fno); /* Read a directory item */
			if (res != FR_OK || fno.fname[0] == 0)
				break; /* Break on error or end of dir */
			sFiles[countFiles] = fno.fname;
			sFiles[countFiles++].truncate(4);
		}
		f_closedir(&dir);
	}

	int window_start = 0;
	int window_end;
	int index = 0;

	int window_item_count = 6 - 1; //6 реальных
	window_start = 0;
	window_end =
			(countFiles >= window_item_count) ? window_item_count : countFiles;

	uint32_t H = 40;
	uint32_t StartY = 0;

	tft.uTFT.GetColor = 1;

	int needRender = 1;

	while (1) {

		script.run();

		KEY.tick();

		//─ Опрос Энкодера ──────────────────────────────────────┐
		if (Encoder.Left) {
			Encoder.Left = 0;
			index--;
			if (index < 0)
				index = 0;
			if (index < window_start) {
				window_start = index;
				window_end = window_start + window_item_count;
			}
			needRender = 1;
		}

		if (Encoder.Right) {
			Encoder.Right = 0;
			index++;
			if (index >= countFiles)
				index = countFiles - 1;
			if (index > window_end) {
				window_end = index;
				window_start = window_end - window_item_count;
			}
			needRender = 1;
		}
		//─────────────────────────────────────────────────────────┘

		if (needRender) {
			needRender = 0;

			tft.Fill16(COLOR_BACKGROUND); //Фон

			//─ Рисуем список ──────────────────────────────────────┐
			int ii = 0;
			for (int i = window_start; i < window_end; i++) {
				if (i == index)
					tft.RectangleFilled(0, StartY + H * (ii % 6), 239, H,
							COLOR_RECTAGLE);

				sprintf(str, "%s", sFiles[i].buf);
				tft.ConvertStringDosTo1251(str);

				char strUTF8[48];
				tft.ConvertString1251ToUTF8(str, strUTF8);
				SEGGER_RTT_printf(0,
						"\033[04;38;05;226;48;05;24m%d'%s'\x1B[0m\r\n", i,
						strUTF8);

				tft.Font_Smooth_drawStr1251(10, 8 + 40 * (ii % 6), str,
						(i == index) ?
								tft.RGB565(8, 8, 8) :
								tft.RGB565(128, 128, 128));
				ii++;
			}
			//──────────────────────────────────────────────────────┘

			tft.ST7789_UpdateDMA16bitV3();

		}



		if (KEY.isClick()) {
			if (index == 0) return;
			script.load(sFiles[index].buf);
			script.start();
			needRender = 1;
			KEY.isClick();
			script.returnToMenu2 = true;
		}

		if (script.returnToMenu2) return;

		//─ Выход в настройки ─┐
		if (KEY.isHolded())  //│
			return;          //│
		//─────────────────────┘
	}

}
