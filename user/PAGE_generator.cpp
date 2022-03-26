#include "Page.h"
#include "global_define.h"
#include "stdio.h"

extern Bitmap bmpBackground240240;

extern Bitmap bmp_on_3232;
extern Bitmap bmp_off_3232;

static int temp;
static PAGE_Menu_item_typedef   * temp_item;
static PAGE_Menu_config_typedef * temp_menu;


static char * convert_item_modulation(char * s)
{
	static char res_str[20];
	memset(res_str, 0, 20);
	int len = strlen(s);
	if (len > 0)
	  memcpy(res_str, &s[0], len-4);

	return &res_str[0];
}

//Событие по isClick в списке выбора названия несущей
void PageSelectModulation_onClick(void)
{
	int index = temp_menu->index; //Получем индекс в списке
	//char filename[32]={0};
	//sprintf(filename,"%s", temp_item[index].text); //Получаем название несущей по индексу

	if (temp == INDEX_CH1_CR) //Carrier
	{
		sprintf(Gen.CH1.Carrier_mod,"%s", temp_item[index].text);
        Gen.Create_Carrier(&Gen.CH1);
        temp_item[index].exit = 1; //Для выхода
        tft.Font_Smooth_Load(page_generator.font);
	}

	if (temp == INDEX_CH1_AM_MOD) //AM mod
	{
		sprintf(Gen.CH1.AM_mod,"%s", temp_item[index].text);
        Gen.Create_AM_Modulation(&Gen.CH1);
        temp_item[index].exit = 1; //Для выхода
        tft.Font_Smooth_Load(page_generator.font);
	}

	if (temp == INDEX_CH1_FM_MOD) //AM mod
	{
		sprintf(Gen.CH1.FM_mod,"%s", temp_item[index].text);
        Gen.Create_FM_Modulation(&Gen.CH1);
        temp_item[index].exit = 1; //Для выхода
        tft.Font_Smooth_Load(page_generator.font);
	}

	if (temp == INDEX_CH2_CR) //Carrier
	{
		sprintf(Gen.CH2.Carrier_mod,"%s", temp_item[index].text);
        Gen.Create_Carrier(&Gen.CH2);
        temp_item[index].exit = 1; //Для выхода
        tft.Font_Smooth_Load(page_generator.font);
	}

	if (temp == INDEX_CH2_AM_MOD) //AM mod
	{
		sprintf(Gen.CH2.AM_mod,"%s", temp_item[index].text);
        Gen.Create_AM_Modulation(&Gen.CH2);
        temp_item[index].exit = 1; //Для выхода
        tft.Font_Smooth_Load(page_generator.font);
	}

	if (temp == INDEX_CH2_FM_MOD) //AM mod
	{
		sprintf(Gen.CH2.FM_mod,"%s", temp_item[index].text);
        Gen.Create_FM_Modulation(&Gen.CH2);
        temp_item[index].exit = 1; //Для выхода
        tft.Font_Smooth_Load(page_generator.font);
	}
}

//Пре рисуем по index
void postPageSelectModulation(void)
{
	tft.RectangleFilled(0, 0, 239, 119, BLACK);
    int index = temp_menu->index; //Текущий выбранный индекс
    char filename[32]={0};
    UINT testByte;

   if (index)
   {

    //Получаем имя файла для отображения на экране
	if ((temp==INDEX_CH1_CR)||(temp==INDEX_CH2_CR))
		sprintf(filename,"/Carrier/%s", temp_item[index].text);
	else
		sprintf(filename,"/Mod/%s", temp_item[index].text);

	//Открывам файл
	if (f_open(&SDFile, filename, FA_OPEN_EXISTING | FA_READ) == FR_OK) {
			SEGGER_RTT_printf(0, ">Open OK %s\n", filename);
			f_read(&SDFile, &Gen.buffer_temp, 2048, &testByte);
			f_close(&SDFile);
		} else
		{
			SEGGER_RTT_printf(0, ">Open Error %s\n", filename);
			return;
		}

		uint16_t *p;
	    p = (uint16_t*)&Gen.buffer_temp[0];
	    Gen.buffer_temp[1024] = Gen.buffer_temp[1023];
	    Gen.buffer_temp[1025] = Gen.buffer_temp[1023];

	    //Carrier
	   if ((temp == INDEX_CH1_CR)||(temp == INDEX_CH2_CR))
	   {
	    tft.LineHW(0, 59, 239, BLUE);

	    tft.LineMoveXY(17, (4095-*p)/40 + 8);

		for (int i = 0; i < 1024; i+=5){
			tft.LineMoveTo(17+i/10, (4095-*p)/40 + 8, GREEN);
		    p+=5;
		}
		p = (uint16_t*)&Gen.buffer_temp[0];
	    //tft.LineMoveXY(17, *p/40 + 8);
		for (int i = 0; i < 1024; i+=5){
			tft.LineMoveTo(119+i/10, (4095-*p)/40 + 8, GREEN);
		    p+=5;
		}
	   }

	    //AM Mod
	   if ((temp==INDEX_CH1_AM_MOD)||(temp==INDEX_CH1_FM_MOD)||(temp==INDEX_CH2_AM_MOD)||(temp==INDEX_CH2_FM_MOD))
	   {
	    tft.LineHW(0, 59, 239, BLUE);
	    tft.LineMoveXY(17, *p/40 + 8);
		for (int i = 0; i < 1024; i+=5){
			tft.LineV(17+i/5, (4095-*p)/80 + 8, (*p)/80 + 59, GREEN);
		    p+=5;
		}
	   }

    } //if (index)

   tft.needUpdate = 1;
}

//Создаем списки и по ним рендерим графику и рисуем списки
void PAGE_generator_select_modulation(void)
{
	uint32_t i = page_generator.index;

	//Поиск файлов в папке
	char * path;

	if ((i==INDEX_CH1_CR)||(i==INDEX_CH2_CR))
	  path = (char*)"/Carrier";
	else
	  path = (char*)"/Mod";

	temp = i; //Определяет тип модуляции несущая или модуляция

    static FRESULT res;
    DIR dir;
    static FILINFO fno;
    Dir_File_Info[0].maxFileCount = 0;

    res = f_opendir(&dir, path);                       /* Open the directory */

    if (res == FR_OK) {
        for (;;) {
					res = f_readdir(&dir, &fno);                   /* Read a directory item */
					if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
					sprintf(Dir_File_Info[Dir_File_Info[0].maxFileCount++].Name,"%s", fno.fname);
        }
        f_closedir(&dir);
    }

    PAGE_Menu_item_typedef    item[Dir_File_Info[0].maxFileCount+1] = {0};
    PAGE_Menu_config_typedef  menu = {0};

    sprintf(item[0].text, "%s","<-Назад");
    item[0].exit = 1; //Для выхода

    for(int i = 1; i<Dir_File_Info[0].maxFileCount+1;i++){
    	sprintf(item[i].text, "%s",Dir_File_Info[i-1].Name);
    	item[i].callBackFunc_isClick = &PageSelectModulation_onClick;
    }


	//Описание как рендерить меню
    menu.item_count   = 4;
    menu.item_height  = 30;
    menu.item_start_y = 120;
    menu.font = (uint8_t *)(tft.getResAdressFontID(1)); //&_acRoboto_Medium_en_ru_18[0];
    menu.encoder_block = 0;
    menu.postCallBackFunc = NULL;
    menu.preCallBackFunc  = NULL;
    menu.temp = 0;
    //menu.title = NULL;
    menu.postCallBackFunc = &postPageSelectModulation; //Рисовалка
    menu.count_item = Dir_File_Info[0].maxFileCount+1;



    temp_item = &item[0];
    temp_menu = &menu;

    PAGE_Menu( &menu,  &item[0], Dir_File_Info[0].maxFileCount+1);
    tft.Font_Smooth_Load(page_setting.font);

#ifdef USE_CLI
    if (page_generator.index <12)
    	sendStructCHtoHost(0);
    else
    	sendStructCHtoHost(1);
#endif


}



void PAGE_generator_CH1_CH_EN_switch(void)
{
	if (Gen.CH1.CH_EN)
	  Gen.CH1.CH_EN = 0;
    else
	  Gen.CH1.CH_EN = 1;
#ifdef USE_CLI
    sendStructCHtoHost(0);
#endif
}

void PAGE_generator_CH1_AM_EN_switch(void)
{ if (Gen.CH1.AM_EN) Gen.CH1.AM_EN = 0; else Gen.CH1.AM_EN = 1;
#ifdef USE_CLI
    sendStructCHtoHost(0);
#endif
}

void PAGE_generator_CH1_FM_EN_switch(void)
{ if (Gen.CH1.FM_EN) Gen.CH1.FM_EN = 0; else Gen.CH1.FM_EN = 1;
#ifdef USE_CLI
    sendStructCHtoHost(0);
#endif
}

void PAGE_generator_CH2_CH_EN_switch(void)
{ if (Gen.CH2.CH_EN) Gen.CH2.CH_EN = 0; else Gen.CH2.CH_EN = 1;
#ifdef USE_CLI
    sendStructCHtoHost(1);
#endif
}

void PAGE_generator_CH2_AM_EN_switch(void)
{ if (Gen.CH2.AM_EN) Gen.CH2.AM_EN = 0; else Gen.CH2.AM_EN = 1;
#ifdef USE_CLI
    sendStructCHtoHost(1);
#endif
}

void PAGE_generator_CH2_FM_EN_switch(void)
{ if (Gen.CH2.FM_EN) Gen.CH2.FM_EN = 0; else Gen.CH2.FM_EN = 1;
#ifdef USE_CLI
	sendStructCHtoHost(1);
#endif
}

//Включение отключение блокировки
void PAGE_generator_encoder_block_switch(void)
{ if (page_generator.encoder_block) page_generator.encoder_block = 0; else page_generator.encoder_block = 1; }

//Пред функция для картинки генератор, обрабатывем крутилки
void prePageGenerator(void)
{
	uint32_t i = page_generator.index;
	uint32_t temp;
	float    tempf;

	if (page_generator.encoder_block){

        ///////////////////////////////////////
		if (i == INDEX_CH1_FR) //CH1 Carrier Fr
		{
			    temp = Gen.CH1.Carrier_fr;
				if (Encoder.Left) {
					Encoder.Left = 0;
					temp -=100;
					if (temp < 200) temp = 200;
					Gen.CH1.Carrier_fr = temp;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;
					temp +=100;
					if (temp > 4000) temp = 4000;
					Gen.CH1.Carrier_fr = temp;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}
				sprintf(page_item_generator[INDEX_CH1_FR].text,"* %d *", Gen.CH1.Carrier_fr);

		}

		if (i == INDEX_CH2_FR) //CH2 Carrier Fr
		{
		    temp = Gen.CH2.Carrier_fr;
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp -=100;
				if (temp < 200) temp = 200;
				Gen.CH2.Carrier_fr = temp;
#ifdef USE_CLI
				sendStructCHtoHost(1);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp +=100;
				if (temp > 4000) temp = 4000;
				Gen.CH2.Carrier_fr = temp;
#ifdef USE_CLI
				sendStructCHtoHost(1);
#endif
			}
			sprintf(page_item_generator[INDEX_CH2_FR].text,"* %d *", Gen.CH2.Carrier_fr);

		}
		///////////////////////////////////////
		if (i == INDEX_CH1_AM_FR) //CH1 AM Fr
		{
			    tempf = Gen.CH1.AM_fr;

				if (Encoder.Left) {
					Encoder.Left = 0;

					if (tempf <= 10.0F)
						tempf -=0.1F;
					else
						tempf -=1.0F;

					if (tempf < 0.1F) tempf = 0.1F;

					Gen.CH1.AM_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;

					if (tempf< 10.0F)
					  tempf +=0.1F;
					else
					  tempf +=1.0F;

					if (tempf> 100.0F) tempf = 100.0F;

					Gen.CH1.AM_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}
				sprintf(page_item_generator[INDEX_CH1_AM_FR].text,"> %.1f Hz <", Gen.CH1.AM_fr);
		}

		if (i == INDEX_CH2_AM_FR) //CH1 AM Fr
		{
			    tempf = Gen.CH2.AM_fr;

				if (Encoder.Left) {
					Encoder.Left = 0;

					if (tempf <= 10.0F)
						tempf -=0.1F;
					else
						tempf -=1.0F;

					if (tempf < 0.1F) tempf = 0.1F;

					Gen.CH2.AM_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;

					if (tempf< 10.0F)
					  tempf +=0.1F;
					else
					  tempf +=1.0F;

					if (tempf> 100.0F) tempf = 100.0F;

					Gen.CH2.AM_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}
				sprintf(page_item_generator[INDEX_CH2_AM_FR].text,"> %.1f Hz <", Gen.CH2.AM_fr);
		}
		///////////////////////////////////////
		if (i == INDEX_CH1_FM_BASE) //CH1 FM Base
		{
				if (Encoder.Left) {
					Encoder.Left = 0;
					temp = Gen.CH1.FM_Base;
					temp -=100;
					if (temp < 200) temp = 200;
					Gen.CH1.FM_Base = temp;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;
					temp = Gen.CH1.FM_Base;
					temp +=100;
					if (temp > 5000) temp = 5000;
					Gen.CH1.FM_Base = temp;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}
				sprintf(page_item_generator[INDEX_CH1_FM_BASE].text," Base * %d *", Gen.CH1.FM_Base);
		}

		if (i == INDEX_CH2_FM_BASE) //CH1 FM Base
		{
				if (Encoder.Left) {
					Encoder.Left = 0;
					temp = Gen.CH2.FM_Base;
					temp -=100;
					if (temp < 200) temp = 200;
					Gen.CH2.FM_Base = temp;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;
					temp = Gen.CH2.FM_Base;
					temp +=100;
					if (temp > 5000) temp = 5000;
					Gen.CH2.FM_Base = temp;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}
				sprintf(page_item_generator[INDEX_CH2_FM_BASE].text," Base * %d *", Gen.CH2.FM_Base);
		}

		///////////////////////////////////////
		if (i == INDEX_CH1_FM_DEV) //CH1 FM Dev
		{
				if (Encoder.Left) {
					Encoder.Left = 0;
					temp = Gen.CH1.FM_Dev;
					temp -=100;
					if (temp < 200) temp = 200;
					Gen.CH1.FM_Dev = temp;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;
					temp = Gen.CH1.FM_Dev;
					temp +=100;
					if (temp > 5000) temp = 5000;
					Gen.CH1.FM_Dev = temp;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}
				sprintf(page_item_generator[INDEX_CH1_FM_DEV].text," Dev * %d *", Gen.CH1.FM_Dev);
		}

		if (i == INDEX_CH2_FM_DEV) //CH1 FM Dev
		{
				if (Encoder.Left) {
					Encoder.Left = 0;
					temp = Gen.CH2.FM_Dev;
					temp -=100;
					if (temp < 200) temp = 200;
					Gen.CH2.FM_Dev = temp;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;
					temp = Gen.CH2.FM_Dev;
					temp +=100;
					if (temp > 5000) temp = 5000;
					Gen.CH2.FM_Dev = temp;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}
				sprintf(page_item_generator[INDEX_CH2_FM_DEV].text," Dev * %d *", Gen.CH2.FM_Dev);
		}



		if (i == INDEX_CH1_FM_FR) //CH1 FM_mod_fr
		{
			    tempf = Gen.CH1.FM_mod_fr;

				if (Encoder.Left) {
					Encoder.Left = 0;
					if (tempf <= 10.0F)
						tempf -=0.1F;
					else
						tempf -=1.0F;
					if (tempf < 0.1F) tempf = 0.1F;
					Gen.CH1.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;
					if (tempf< 10.0F)
					  tempf +=0.1F;
					else
					  tempf +=1.0F;
					if (tempf> 100.0F) tempf = 100.0F;
					Gen.CH1.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
				}
				sprintf(page_item_generator[INDEX_CH1_FM_FR].text,"> %.1f Hz <", Gen.CH1.FM_mod_fr);
		}

		if (i == INDEX_CH2_FM_FR) //CH1 FM_mod_fr
		{
			    tempf = Gen.CH2.FM_mod_fr;

				if (Encoder.Left) {
					Encoder.Left = 0;

					if (tempf <= 10.0F)
						tempf -=0.1F;
					else
						tempf -=1.0F;

					if (tempf < 0.1F) tempf = 0.1F;

					Gen.CH2.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}

				if (Encoder.Right) {
					Encoder.Right = 0;

					if (tempf< 10.0F)
					  tempf +=0.1F;
					else
					  tempf +=1.0F;
					if (tempf> 100.0F) tempf = 100.0F;
					Gen.CH2.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(1);
#endif
				}
				sprintf(page_item_generator[INDEX_CH2_FM_FR].text,"> %.1f Hz <", Gen.CH2.FM_mod_fr);
		}

		tft.needUpdate = 1;
	}
	else
	{
		//Обновляем названия структуры по структуре CH1 и CH2
		if (Gen.CH1.CH_EN)
		  sprintf(page_item_generator[0].text,"CH1 [  Вкл  ]");
		else
		  sprintf(page_item_generator[0].text,"CH1 [ Откл ]");

	    sprintf(page_item_generator[1].text," %d Hz", Gen.CH1.Carrier_fr);


		sprintf(page_item_generator[2].text," %s", convert_item_modulation(Gen.CH1.Carrier_mod));

		if (Gen.CH1.AM_EN)
		  sprintf(page_item_generator[3].text,"AM [  Вкл  ]");
		else
		  sprintf(page_item_generator[3].text,"AM [ Откл ]");

		sprintf(page_item_generator[4].text," %s", convert_item_modulation(Gen.CH1.AM_mod));
		sprintf(page_item_generator[5].text," %.1f Hz", Gen.CH1.AM_fr);

		if (Gen.CH1.FM_EN)
		  sprintf(page_item_generator[6].text,"FM [  Вкл  ]");
		else
		  sprintf(page_item_generator[6].text,"FM [ Откл ]");

		sprintf(page_item_generator[7].text," Base %d Hz", Gen.CH1.FM_Base);
		sprintf(page_item_generator[8].text," Dev   %d Hz", Gen.CH1.FM_Dev);
		sprintf(page_item_generator[9].text," %s", convert_item_modulation(Gen.CH1.FM_mod));
		sprintf(page_item_generator[10].text," %.1f Hz", Gen.CH1.FM_mod_fr);

		char str[16];
		sprintf(str, "---DMA{%.1f}---", DMA_zagruzka);
		sprintf(page_item_generator[11].text, str);

		if (Gen.CH2.CH_EN)
		  sprintf(page_item_generator[12].text,"CH2 [  Вкл  ]");
		else
		  sprintf(page_item_generator[12].text,"CH2 [ Откл ]");

		sprintf(page_item_generator[13].text," %d Hz", Gen.CH2.Carrier_fr);

		sprintf(page_item_generator[14].text," %s", convert_item_modulation(Gen.CH2.Carrier_mod));

		if (Gen.CH2.AM_EN)
		  sprintf(page_item_generator[15].text,"AM [  Вкл  ]");
		else
		  sprintf(page_item_generator[15].text,"AM [ Откл ]");

		sprintf(page_item_generator[16].text," %s", convert_item_modulation(Gen.CH2.AM_mod));
		sprintf(page_item_generator[17].text," %.1f Hz", Gen.CH2.AM_fr);

		if (Gen.CH2.FM_EN)
		  sprintf(page_item_generator[18].text,"FM [  Вкл  ]");
		else
		  sprintf(page_item_generator[18].text,"FM [ Откл ]");

		sprintf(page_item_generator[19].text," Base %d Hz", Gen.CH2.FM_Base);
		sprintf(page_item_generator[20].text," Dev   %d Hz", Gen.CH2.FM_Dev);
		sprintf(page_item_generator[21].text," %s", convert_item_modulation(Gen.CH2.FM_mod));
		sprintf(page_item_generator[22].text," %.1f Hz", Gen.CH2.FM_mod_fr);


	}
}





