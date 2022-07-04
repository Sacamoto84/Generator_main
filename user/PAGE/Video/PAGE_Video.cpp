#include "Page.h"

#include "global_define.h"
#include "stdio.h"

 typedef struct
 {
   char text [20];
 } item_files;


 uint32_t callback_video_stop(uint32_t i)
 {
	 KEY.isRelease();
	 KEY.tick();
	 if (KEY.isRelease())
	 {
		tft.video_stop = 1; //Передать user прекратить повторный запуск видео
		return 1;           // -> 1 остановить воспроизведение
	 }
	 return 0;
 }


void PAGE_Video(void) {
	    char str [32];
	    static FRESULT res;
	    DIR dir;
	    FILINFO fno;

	    Dir_File_Info_Array Dir_File_Info[32]; //Массив всех файлов в папке

	    Dir_File_Info[0].maxFileCount = 0;
	    memset(&Dir_File_Info, 0, sizeof(Dir_File_Info_Array)*32);
	    res = f_opendir(&dir, (char*)"/video");                       /* Open the directory */
	    if (res == FR_OK) {
	        for (;;) {
				res = f_readdir(&dir, &fno);                   /* Read a directory item */
				if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
				   if (strstr (fno.fname, "rawi") == NULL)
				   {
					   memset(str, 0, 32);
					   strncpy (str, fno.fname, strlen(fno.fname) - 4);
					   sprintf(Dir_File_Info[Dir_File_Info[0].maxFileCount++].Name,"%s", str);
				   }
	        }
	        f_closedir(&dir);
	    }

	int count;
	count = Dir_File_Info[0].maxFileCount;

	int window_start = 0;
	int window_end;
	int index = 0;

	int window_item_count = 6 - 1; //6 реальных
	window_start = 0;
	window_end = (count >= window_item_count) ? window_item_count : count;

	uint32_t H = 40;
	uint32_t StartY = 0;

	tft.uTFT.GetColor = 1;
	tft.videoCallBackFunc = &callback_video_stop;

	int needRender = 1;

	while (1) {
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
			if (index >= count)
				index = count - 1;
			if (index > window_end) {
				window_end = index;
				window_start = window_end - window_item_count;
			}

			needRender = 1;

		}
		//─────────────────────────────────────────────────────────┘


		if(needRender){
			needRender = 0;

			tft.Fill16(COLOR_BACKGROUND); //Фон

		//─ Рисуем список ──────────────────────────────────────┐
		int ii = 0;
		for (int i = window_start; i <= window_end; i++) {
			if (i == index)	tft.RectangleFilled(0, StartY + H * (ii % 6), 239, H, COLOR_RECTAGLE);
			sprintf(str, "%s", Dir_File_Info[i].Name);
			tft.ConvertStringDosTo1251 ( str );

			char strUTF8[48];
			tft.ConvertString1251ToUTF8(str, strUTF8);
			SEGGER_RTT_printf(0, "\033[04;38;05;226;48;05;24m%d'%s'\x1B[0m\r\n", i,  strUTF8 );

			tft.Font_Smooth_drawStr1251(10, 8 + 40 * (ii % 6), str , (i == index)? tft.RGB565(8, 8, 8) : tft.RGB565(128, 128, 128));
			ii++;
		}
		//──────────────────────────────────────────────────────┘

		    tft.ST7789_UpdateDMA16bitV3();

		}

		    if (KEY.isClick()) {

             int time = 0;
             sprintf(str, "/video/%s.rawi",  Dir_File_Info[index].Name); //Путь до файла описания видео
             res = f_open(&SDFile, str, FA_READ );
             if (res == FR_OK)
             {
            	SEGGER_RTT_printf(0, "res == FR_OK\r\n");
            	UINT * br;
            	*br = 0;
            	res = f_read (&SDFile, &str, 16, br); //Читаем строку времени задержки
            	if (res == FR_OK)
            	   time =  atoi(str); //Получили время кадра в ms
             }
             f_close(&SDFile);

              sprintf(str, "/video/%s.raw",  Dir_File_Info[index].Name);
              tft.video_stop = 0;

              while(tft.video_stop == 0)   //Пока tft.video_stop == 0, ->1 callback
              {
            	tft.video_play(str, time); //Запускаем видео (path, время кадра)
              }

              needRender = 1;

              KEY.isClick();
            }


		//─ Выход в настройки ─┐
		if (KEY.isHolded())  //│
			return;          //│
		//─────────────────────┘
	}

}
