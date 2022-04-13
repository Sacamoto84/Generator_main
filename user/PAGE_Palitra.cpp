#include "Page.h"

#include "global_define.h"

#include "stdio.h"

// Конвертирование строки из DOS(866) в Win1251
void ConvertStringDosTo1251 ( char *str )
{
	static const uint8_t table[128] = {
			0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,	// 00 - 0F
			0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, // 10 - 1F
			0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, // 20 - 2F
			0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, // 30 - 3F
			0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, // 40 - 4F
			0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, // 50 - 5F
			0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF, // 60 - 6F
			0xA8, 0xB8, 0xAA, 0xBA, 0xAF, 0xDF, 0xA1, 0xA2, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF  // 70 - 7F
	};
	int i;

	for ( i = 0; i < strlen ( str ); i ++ )
		if ( str [ i ] > 127 )
			str [ i ] = table [ (int) (str[i] - 128) ];
} // ConvertStringDosTo1251

// Конвертирование строки из Win1251 в DOS(866)
void ConvertString1251ToDos ( char *str )
{
	static const uint8_t table[128] = {
			0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, // 00 - 0F
			0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, // 10 - 1F
			0xD0, 0xF6, 0xF7, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xF0, 0xD9, 0xF2, 0xDB, 0xDC, 0xDD, 0xDE, 0xF4, // 20 - 2F
			0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF1, 0xF9, 0xF3, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF, // 30 - 3F
			0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, // 40 - 4F
			0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0xF5, // 50 - 5F
			0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, // 60 - 6F
			0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF  // 70 - 7F
	};
	int i;

	for ( i = 0; i < strlen ( str ); i ++ )
		if ( str [ i ] > 127 )
			str [ i ] = table [ (int)(str[i] - 128) ];
} // ConvertStringDosTo1251

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
		tft.video_stop = 1;
		return 1;
	 }

	 return 0;
 }


void PAGE_Video(void) {
	    char str [32];
	    static FRESULT res;
	    DIR dir;
	    FILINFO fno;
	    Dir_File_Info[0].maxFileCount = 0;
	    memset(&Dir_File_Info, 0, sizeof(Dir_File_Info_Array)*50);
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
	int max_item = count;

	int window_item_count = 6 - 1; //6 реальных
	window_start = 0;
	window_end = (count >= window_item_count) ? window_item_count : count;

	uint32_t H = 40;
	uint32_t StartY = 0;

	tft.uTFT.GetColor = 1;
	tft.videoCallBackFunc = &callback_video_stop;

	while (1) {
		KEY.tick();

			if (Encoder.Left) {
				Encoder.Left = 0;
				index--;
				if (index < 0)
					index = 0;
				if (index < window_start) {
					window_start = index;
					window_end = window_start + window_item_count;
				}
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
			}

			tft.Fill(COLOR_BACKGROUND); //Фон

			int ii = 0;
		    for (int i = window_start; i <= window_end; i++) {
				if (i == index)	tft.RectangleFilled(0, StartY + H * (ii % 6), 239, H, COLOR_RECTAGLE);
				sprintf(str, "%s", Dir_File_Info[i].Name);
				ConvertStringDosTo1251 ( str );
				tft.Font_Smooth_drawStr1251(10, 8 + 40 * (ii % 6), str , (i == index)? tft.RGB565(8, 8, 8) : tft.RGB565(128, 128, 128));
			    ii++;
			}

		    tft.ST7789_UpdateDMA16bitV3();

		    if (KEY.isClick()) {

             int time = 0;
             sprintf(str, "/video/%s.rawi",  Dir_File_Info[index].Name);
             res = f_open(&SDFile, str, FA_READ );
             if (res == FR_OK)
             {
            	SEGGER_RTT_printf(0, "res == FR_OK\n");
            	UINT * br;
            	*br = 0;
            	res = f_read (&SDFile, &str, 16, br);
            	if (res == FR_OK)
            	   time =  atoi(str);
             }
             f_close(&SDFile);
             sprintf(str, "/video/%s.raw",  Dir_File_Info[index].Name);

              tft.video_stop = 0;
              while(tft.video_stop == 0)
              {
            	tft.video_play(str, time);
              }
              KEY.isClick();
            }

		if (KEY.isHolded())
			return;

	}

}
