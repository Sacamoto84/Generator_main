#include "Page.h"
#include "global_define.h"

#include "SEGGER.h"
#include "SEGGER_SYSVIEW.h"
#include "stdio.h"

#include "BLE_Commands.h"

#include "TFT_Wiget_Animated_Rectagle.h"

#include "TFT_gif.h"


extern Bitmap bmpBackground240240;

extern void BLE_Task(void);

#define maxString 32 // ограничиваем строку шириной экрана
char target[maxString + 1] CCMRAM= "";

char* utf8rus2(char *source) {
	int i, j, k;
	unsigned char n;
	char m[2] = { '0', '\0' };
	strcpy(target, "");
	k = strlen(source);
	i = j = 0;
	while (i < k) {
		n = source[i];
		i++;

		if (n >= 127) {
			switch (n) {
			case 208: {
				n = source[i];
				i++;
				if (n == 129) {
					n = 192;
					break;
				} // перекодируем букву Ё
				break;
			}
			case 209: {
				n = source[i];
				i++;
				if (n == 145) {
					n = 193;
					break;
				} // перекодируем букву ё
				break;
			}
			}
		}

		m[0] = n;
		strcat(target, m);
		j++;
		if (j >= maxString)
			break;
	}
	return target;
}

void PAGE_Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t select, char *str) {

	if (select) {
		tft.RectangleFilled(x, y, w, h, palitra[2]);
		tft.LineH(y, x, x + w, palitra[3]);
		tft.LineV(x, y, y + h, palitra[3]);

		tft.LineH(y + h, x + 1, x + w - 1, palitra[4]);
		tft.LineV(x + w, y + 1, y + h, palitra[4]);

		tft.LineH(y + h + 1, x + 1, x + w + 1, palitra[15]);
		tft.LineV(x + w + 1, y + 1, y + h + 1, palitra[15]);
	} else {
		tft.RectangleFilled(x, y, w, h, palitra[1]);
		tft.LineH(y, x, x + w, palitra[5]);
		tft.LineV(x, y, y + h, palitra[5]);

		tft.LineH(y + h, x + 1, x + w - 1, palitra[6]);
		tft.LineV(x + w, y + 1, y + h, palitra[6]);

		tft.LineH(y + h + 1, x + 1, x + w + 1, palitra[15]);
		tft.LineV(x + w + 1, y + 1, y + h + 1, palitra[15]);
	}

	gfxfont.set_delta_x(2);
	gfxfont.Puts(x + 15, y + 20, str);

	//u8g_SetFont(u8g_font_profont29);
	//uTFT_SetFontColor(BLACK, WHITE);
	//u8g_DrawStr(x + 15, y + (h+u8g.font_ref_ascent)/2, str );
}

//Нажатая кнопка
void PAGE_Button_Pressed(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		char *str) {

	tft.RectangleFilled(x, y, w, h, 2); // Светлый фон выбранной кнопки

	tft.LineH(y, x, x + w, 6);      // Темная часть окантовки темной кнопки
	tft.LineH(y + 1, x, x + w, 6);  // Темная часть окантовки темной кнопки

	tft.LineV(x, y, y + h, 6);      // Темная часть окантовки темной кнопки
	tft.LineV(x + 1, y, y + h, 6);  // Темная часть окантовки темной кнопки

	tft.LineH(y + h, x + 1, x + w - 1, 5); // Светлая часть окантовки темной кнопки
	tft.LineH(y + h - 1, x + 2, x + w - 1, 5); // Светлая часть окантовки темной кнопки

	tft.LineV(x + w, y + 1, y + h, 5);  // Светлая часть окантовки темной кнопки
	tft.LineV(x + w - 1, y + 2, y + h, 5); // Светлая часть окантовки темной кнопки

	tft.GotoXY(x + 15, 20);
	//gfxfont.set_delta_x(2);
	gfxfont.Puts(str);

	//u8g_SetFont(u8g_font_profont29);
	//uTFT_SetFontColor(BLACK, WHITE);
	//u8g_DrawStr(x + 15, y + (h+u8g.font_ref_ascent)/2, str );
}

//Создание звднего фона
void PAGE_Background_Board(void) {
	//

	SEGGER_SYSVIEW_Warn("Fill(0)");
	tft.Fill(palitra[0]); //Окантовка

	SEGGER_SYSVIEW_Warn("RectangleFilled");
	//tft.RectangleFilled(5, 5, 229, 229, 1); //Основной фон
	tft.RectangleFilled(5, 5, 229, 229, palitra[15]); //Основной фон

	//Темное
	SEGGER_SYSVIEW_Warn("LineH");
	tft.LineH(5, 5, 234, palitra[7]);
	SEGGER_SYSVIEW_Warn("LineH");
	tft.LineH(6, 5, 234, palitra[7]);

	SEGGER_SYSVIEW_Warn("LineV");
	tft.LineV(5, 5, 234, palitra[7]);
	SEGGER_SYSVIEW_Warn("LineV");
	tft.LineV(6, 5, 234, palitra[7]);

	//Светлое
	SEGGER_SYSVIEW_Warn("LineH");
	tft.LineH(234, 5, 234, palitra[9]);
	SEGGER_SYSVIEW_Warn("LineH");
	tft.LineH(233, 6, 234, palitra[9]);

	SEGGER_SYSVIEW_Warn("LineV");
	tft.LineV(233, 6, 234, palitra[9]);
	SEGGER_SYSVIEW_Warn("LineV");
	tft.LineV(234, 5, 234, palitra[9]); //uTFT_VLine(234 , 5, 234, RGB565(186,207,178));
}

void PAGE_Menu(menu_typedef *menu, item_typedef *item,
		int NUM) {

	Gen.pause();

	tft.Font_Smooth_Load(menu->font);

	volatile uint8_t i;

	uint8_t index = 0;

	int max_imem;
	int max_window_item;
	int window_start;
	int window_end;

	max_imem = NUM; //NUM_OF(&item);

	max_window_item = menu->item_count - 1; //6 реальных
	window_start = 0;
	window_end = (max_imem >= max_window_item) ? max_window_item : max_imem;

	void (*func_name)(void); //объявляем указатель на функцию

	uint32_t H = menu->item_height;
	uint32_t StartY = menu->item_start_y;

	tft.needUpdate = 1;

	TFT_Wiget_Animated_Rectagle B[max_imem];

	for (int i = 0; i < max_imem; i++) {
		B[i].init_tft(&tft);
		B[i].setHW(H, 230);
		B[i].typeAnimation = 2;
	}

	//B[0].typeAnimation = 0;
	//B[1].typeAnimation = 0;

	int gif_count = 0;  //Количество гифок
	for (int i = 0; i < max_imem; i++) {
		if (item[i].nameGif)
			gif_count++;
	}

	TFT_gif gif1[gif_count];
	//Bitmap  bmp [gif_count];
	int8_t id;

	if (gif_count) {
		gif_count = 0;

		for (int i = 0; i < max_imem; i++) {

			if (item[i].nameGif) {

				item[i].gif = &gif1[gif_count];

				item[i].gif->init(&tft);
				item[i].gif->setName(item[i].nameGif);

                id = item[i].resid_first;
				item[i].gif->bmpStop = tft.getResBitmapID(id);

				item[i].gif->setDelay(0);

				item[i].gif->setX(item[i].gif_x);

				item[i].gif->trigger = item[i].gif_trigger;

				if (item[i].gif_init_state != NULL)
				{
					if (*item[i].gif_init_state != 0)
						item[i].gif->setIndexMax();
				}

				gif_count++;
			}

		}
	}

	//item[1].gif->field.bit32 = 0;



	char str[64];

	menu->field.needUpdate = 1;

	while (1) {

		KEY.tick();

		//tft.needUpdate = 0;




		if (menu->preCallBackFunc) {
			menu->index = index;
			func_name = menu->preCallBackFunc;
			func_name();
		}



		//Блокировка энкодера, нужно чтобы обрабатывать в пре
		if (menu->field.encoder_block == 0) {
			if (Encoder.Left) {
				Encoder.Left = 0;
				index--;
				if (index > 127)
					index = 0;
				if (index < window_start) {
					window_start = index;
					window_end = window_start + max_window_item;
				}
				menu->field.needUpdate = 1;
				//tft.needUpdate = 1;
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				index++;
				if (index >= max_imem)
					index = max_imem - 1;
				if (index > window_end) {
					window_end = index;
					window_start = window_end - max_window_item;
				}
				//tft.needUpdate = 1;
				menu->field.needUpdate = 1;
			}
		}

		menu->window_start = window_start;
		menu->window_end = window_end;
		menu->index = index;
		menu->max_item = max_imem - 1;

		//tft.needUpdate = 1;

		tft.Fill(menu->ColorBackground); //Фон

		//Фон
		//tft.Bitmap_From_Flash_Background_16bit(&bmpBackground240240); // 756us

		//if (index < 12)
		//	tft.Gradient_Vertical(0, 0, 239, 239, 0x12, 0x0C, 0x6E, 0x0B, 0x07,
		//			0x42); //670us
		//else
		//	tft.Gradient_Vertical(0, 0, 239, 239, 0x4D, 0x44, 0x6f, 0x26, 0x4d,
		//			0x59);

		//tft.Gradient_Vertical(0, 0, 239, 239, 0x26, 0x4d, 0x59, 0x43, 0x97, 0x8d);
		//tft.Gradient_Vertical(0, 0, 239, 239, 0x68, 0x82, 0xa0, 0x2c, 0x69, 0x75);
		//tft.Gradient_Vertical(0, 0, 239, 239, 0x26, 0x4d, 0x59, 0x2c, 0x69, 0x75);
		//tft.BMP_From_File(0, 0, "b10.bmp");

		//tft.LineH(0  + (index - window_start) * H + StartY, 0, 239,  palitra[17]);
		//tft.LineH(1  + (index - window_start) * H + StartY, 0, 239,  palitra[17]);
		//tft.RectangleFilled(0, 2 + (index - window_start) * H  + StartY, 239, H - 4, palitra[18]);
		//tft.LineH((H-3) + (index - window_start) * H + StartY, 0, 239,	palitra[19]);
		//tft.LineH((H-2) + (index - window_start) * H + StartY, 0, 239, palitra[19]);

		//uint8_t ii;
		//ii = 0;
		//TimerT5.Start();

		menu->ii = 0;
	    for (i = window_start; i <= window_end; i++) {

	    	//if (i == index)
	    	//	B[i].select(1);
	    	//else
	    	//	B[i].select(0);

	    	//B[i].setY(StartY + H * (menu->ii % menu->item_count));
	    	//B[i].run();  //116 us -Of Gen on

	    	if (i == menu->index) tft.RectangleFilled(0, StartY + H * (menu->ii % menu->item_count), 239, H, palitra[18]);


            menu->run(i);


    		if (item[i].gif) {

    				//if (i == index)
    				//	item[i].gif->command(PLAY);
    				//else
    				//	item[i].gif->command(STOP);

    				item[i].gif->setY(StartY + H * (menu->ii % menu->item_count));
    				item[i].gif->run(); //32x32x32 4800us(914285 Байт/Сек) -Of Gen Off    5000us Gen On 4096байт
    				sprintf(str, "item[%d].gif->run();", i);
    				LOG((char*)"MENU",'I',str);
    			}


    		if (B[i].needUpdate()) {
    				sprintf(str, "B[%d].needUpdate()", i);
    				LOG((char*)"MENU",'I',str);
    				//List_Update_Particle U;
    				//U = B[i].info();
    			//	U.y1 += 1;
    				tft.ST7789_Update(B[i].info());
    				//SEGGER_RTT_printf(0, "i:%d H:%d W:%d x0:%d y0:%d x1:%d y1:%d\n",
    				//	i, U.H, U.W, U.x0, U.y0, U.x1, U.y1);
    			}

    		if (item[i].gif) {tft.ST7789_Update(item[i].gif->info());}

    		menu->ii++;
	    }



		//TimerT5.Loger("for (i = window_start; i <= window_end; i++)");

		//menu->verticalScroll = 1;
		//TimerT5.Start();

		//Рисуем вертикальный скролл //87 us
		if (menu->field.verticalScroll) {
			tft.RectangleFilled(230, menu->item_start_y, 14,
					menu->item_count * menu->item_height, tft.RGB565(0, 0, 0));
			int H = (menu->item_count * menu->item_height) - 4; //Общая высота области в которой идет рисование
			float Hw =
					H
							* ((float) (menu->item_count)
									/ (float) (menu->max_item + 1)); //Размер самого ползунка
			float delta = float(H - Hw)
					/ (float) (menu->max_item + 1 - menu->item_count);
			tft.RectangleFilled(222 + 5 + 5,
					menu->item_start_y + 2 + delta * (menu->window_start),
					10 - 5, Hw, tft.RGB565(205, 205, 205));
		}
		//TimerT5.Loger("verticalScroll");

		if (menu->postCallBackFunc) {
			func_name = menu->postCallBackFunc;
			func_name();
		}


		if ((menu->field.needUpdate) || (tft.needUpdate)) {
			menu->field.needUpdate = 0;
		    LOG((char*)"MENU",'I',(char*)"ST7789_UpdateDMA16bitV3");
			tft.ST7789_UpdateDMA16bitV3(); //DMA8bitV2();
		}

		if (KEY.isHolded()) {
			if (item[index].callBackFunc_isHolded) {
				func_name = item[index].callBackFunc_isHolded;
				func_name();
				tft.needUpdate = 1;
			}
		}

		if (KEY.isDouble()) {
			if (item[index].callBackFunc_isDouble) {
				func_name = item[index].callBackFunc_isDouble;
				func_name();
				tft.needUpdate = 1;
			}
		}

		if (KEY.isClick()) {

			KEY.isHolded();
			KEY.isDouble();

			if (item[index].field.disable == 0)
			{
				if (item[index].callBackFunc_isClick) {
					func_name = item[index].callBackFunc_isClick;
					func_name();
					menu->field.needUpdate = 1; //При выходе из события обновляем экран
				}
			}

			if (item[index].field.exit)
			{
				tft.needUpdate = 1; //При выходе из события обновляем экран
				return;
			}
		}

#ifdef USE_CLI
		BLE_Task();
#endif

		//sendStructCHtoHost(0);

	}

}

