#include "Page.h"
#include "global_define.h"

#include "SEGGER.h"
#include "SEGGER_SYSVIEW.h"
#include "stdio.h"

void PAGE_Setting(void);


void PAGE_init_struct_generator(void)
{
	for(int i = 0; i < NUM_ITEM_GENERETOR ; i++)
	{
		item_generator[i].text_color = -1;
		item_generator[i].callBackFunc_isHolded = &PAGE_Setting;
	}

	//page_item_generator[0].text = (char*) "CH1 ENABLE";
	item_generator[INDEX_CH1_EN].callBackFunc_isClick = &PAGE_generator_CH1_CH_EN_switch;
	item_generator[INDEX_CH1_EN].preCallBackFunc      = &generator_pre_CH1_EN;
	item_generator[INDEX_CH1_EN].gif_init_state       = &Gen.CH1.CH_EN;
	item_generator[INDEX_CH1_EN].resid_last  = OFF;
	item_generator[INDEX_CH1_EN].resid_first = ON;

	//page_item_generator[1].text = (char*) "CH1 1000Hz";
	item_generator[INDEX_CH1_FR].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FR].preCallBackFunc      = &generator_pre_CH1_FR;

	//page_item_generator[2].text = (char*) "CH1 SINUS";
	item_generator[INDEX_CH1_CR].callBackFunc_isClick = &PAGE_generator_select_modulation;

	//page_item_generator[3].text = (char*) "AM Enable";
	item_generator[INDEX_CH1_AM_EN].callBackFunc_isClick = &PAGE_generator_CH1_AM_EN_switch;
	item_generator[INDEX_CH1_AM_EN].preCallBackFunc      = &generator_pre_CH1_AM_EN;
	item_generator[INDEX_CH1_AM_EN].gif_init_state       = &Gen.CH1.AM_EN;
	item_generator[INDEX_CH1_AM_EN].resid_last  = OFF;
	item_generator[INDEX_CH1_AM_EN].resid_first = ON;


	//page_item_generator[4].text = (char*) "AM-CHARP";
	item_generator[INDEX_CH1_AM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;
	//item_generator[INDEX_CH1_AM_MOD].nameGif = (char*)"Q12";
	//page_item_generator[INDEX_CH1_AM_MOD].resid   = 5;

	//page_item_generator[5].text = (char*) "AM-10.4 Hz";
	item_generator[INDEX_CH1_AM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_AM_FR].preCallBackFunc = &generator_pre_CH1_AM_FR;


	//page_item_generator[6].text = (char*) "FM Enable";
	item_generator[INDEX_CH1_FM_EN].callBackFunc_isClick  = &PAGE_generator_CH1_FM_EN_switch;
	item_generator[INDEX_CH1_FM_EN].preCallBackFunc = &generator_pre_CH1_FM_EN;
	/////////////item_generator[INDEX_CH1_FM_EN].nameGif = (char*)"tB";
	item_generator[INDEX_CH1_FM_EN].gif_trigger = MORPH;
	item_generator[INDEX_CH1_FM_EN].gif_init_state = &Gen.CH1.FM_EN;
	item_generator[INDEX_CH1_FM_EN].resid_last  = OFF;
	item_generator[INDEX_CH1_FM_EN].resid_first = ON;


	//page_item_generator[7].text = (char*) "FM-Base 2500";
	item_generator[INDEX_CH1_FM_BASE].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FM_BASE].preCallBackFunc = &generator_pre_CH1_FM_BASE;

	//page_item_generator[8].text = (char*) "FM-Div  200";
	item_generator[INDEX_CH1_FM_DEV].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FM_DEV].preCallBackFunc = &generator_pre_CH1_FM_DEV;


	//page_item_generator[9].text = (char*) "FM-SINus ";
	item_generator[INDEX_CH1_FM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;
	//item_generator[INDEX_CH1_FM_MOD].menu = &menu_generator;

	//page_item_generator[10].text = (char*) "FM-12.5 Hz ";
	item_generator[INDEX_CH1_FM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FM_FR].preCallBackFunc = &generator_pre_CH1_FM_FR;



	//page_item_generator[12].text = (char*) "CH2 EN";
	item_generator[INDEX_CH2_EN].callBackFunc_isClick = &PAGE_generator_CH2_CH_EN_switch;
	item_generator[INDEX_CH2_EN].preCallBackFunc      = &generator_pre_CH2_EN;
	item_generator[INDEX_CH2_EN].gif_init_state       = &Gen.CH2.CH_EN;
	item_generator[INDEX_CH2_EN].resid_last  = OFF;
	item_generator[INDEX_CH2_EN].resid_first = ON;

	//page_item_generator[13].text = (char*) "CR 1000Hz";
	item_generator[INDEX_CH2_FR].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FR].preCallBackFunc      = &generator_pre_CH2_FR;


	//page_item_generator[14].text = (char*) "CR SINUS";
	item_generator[INDEX_CH2_CR].callBackFunc_isClick = &PAGE_generator_select_modulation;

	//page_item_generator[15].text = (char*) "AM EN";
	item_generator[INDEX_CH2_AM_EN].callBackFunc_isClick = &PAGE_generator_CH2_AM_EN_switch;
	item_generator[INDEX_CH2_AM_EN].preCallBackFunc = &generator_pre_CH2_AM_EN;
	item_generator[INDEX_CH2_AM_EN].gif_init_state = &Gen.CH2.AM_EN;
	item_generator[INDEX_CH2_AM_EN].resid_last  = OFF;
	item_generator[INDEX_CH2_AM_EN].resid_first = ON;

	//page_item_generator[16].text = (char*) "--CHARP";
	item_generator[INDEX_CH2_AM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	//page_item_generator[17].text = (char*) "AM 10.4 Hz";
	item_generator[INDEX_CH2_AM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_AM_FR].preCallBackFunc = &generator_pre_CH2_AM_FR;

	//page_item_generator[18].text = (char*) "FM Base 2500";
	item_generator[INDEX_CH2_FM_EN].callBackFunc_isClick  = &PAGE_generator_CH2_FM_EN_switch;
	item_generator[INDEX_CH2_FM_EN].preCallBackFunc = &generator_pre_CH2_FM_EN;
	item_generator[INDEX_CH2_FM_EN].gif_init_state = &Gen.CH2.FM_EN;
	item_generator[INDEX_CH2_FM_EN].resid_last  = OFF;
	item_generator[INDEX_CH2_FM_EN].resid_first = ON;


	//page_item_generator[19].text = (char*) "--Div 200";
	item_generator[INDEX_CH2_FM_BASE].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FM_BASE].preCallBackFunc = &generator_pre_CH2_FM_BASE;

	//page_item_generator[20].text = (char*) "--SIN ";
	item_generator[INDEX_CH2_FM_DEV].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FM_DEV].preCallBackFunc = &generator_pre_CH2_FM_DEV;

	//page_item_generator[21].text = (char*) "--12.5 Hz ";
	item_generator[INDEX_CH2_FM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	item_generator[INDEX_CH2_FM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FM_FR].preCallBackFunc = &generator_pre_CH2_FM_FR;

	//Описание как рендерить меню
	//page_generator.item_count   = 10;
	//page_generator.item_height  = 24;
	menu_generator.item_count   = 11;
	menu_generator.item_height  = 21;
	menu_generator.item_start_y = 0;
	//page_generator.font =  &_acRoboto_Medium_en_ru_18[0];

	menu_generator.item_text_delta_y = -4;

	menu_generator.font = FontId1; //&_acRoboto_Medium_en_ru_30[0];
	menu_generator.preCallBackFunc = &prePageGenerator;
    ////////////////menu_generator.item_text_delta_y = -3;
    menu_generator.field.verticalScroll = 1; //Включит скролл

    menu_generator.items = &item_generator[0];

    menu_generator.ColorBackground = COLOR_BACKGROUND; //Фон

}

void PAGE_init_struct_setting(void) {

	palitra[16] = tft.RGB565(0, 130, 200);
	palitra[17] = tft.RGB565(1, 28, 105);
	palitra[18] = tft.RGB565(2, 78, 153);
	palitra[19] = tft.RGB565(2, 166, 255);
	palitra[20] = tft.RGB565(255, 200, 11);
	palitra[21] = tft.RGB565(5, 56, 122);
	palitra[22] = tft.RGB565(234, 236, 255);
	palitra[23] = tft.RGB565(15, 91, 169);

	//
	sprintf(item_setting[0].text, "Назад");
	item_setting[0].field.exit = 1;

    //
	sprintf(item_setting[1].text, "Сохранить");
	//page_item_setting[1].bmp = &bmpSave13232;
	item_setting[1].nameGif = (char*)"save";
	item_setting[1].gif_trigger = ONCE;
	item_setting[1].gif_x = 170;
	item_setting[1].callBackFunc_isClick = &setting_save_click;


    //
	sprintf(item_setting[2].text, "Загрузить");
	//page_item_setting[2].bmp = &bmpProgram3232;

    //
	sprintf(item_setting[3].text, "Яркость");

	//
	sprintf(item_setting[4].text, "USB MSD");
	item_setting[4].callBackFunc_isClick = &PAGE_MSD; //По нажатию

	//
	sprintf(item_setting[5].text, "Палитра");
	item_setting[5].callBackFunc_isClick = &PAGE_Palitra;


	sprintf(item_setting[6].text, "BT Audio");
	item_setting[6].callBackFunc_isClick = &PAGE_BT_Audio;


	sprintf(item_setting[7].text, "Wiget");
	item_setting[7].callBackFunc_isClick = &PAGE_Volume;


	for(int i = 0; i < 8 ; i++)
	{
		item_setting[i].text_color = -1;

	}

	//Описание как рендерить меню
	menu_setting.item_count   = 6;
	menu_setting.item_height  = 40;
	menu_setting.item_start_y = 0;

	menu_setting.font = Roboto_Medium_en_ru_30; //&_acRoboto_Medium_en_ru_30[0];

	menu_setting.field.verticalScroll = 1; //Включит скролл
	menu_setting.items = item_setting;

	menu_setting.ColorBackground = palitra_COLOR_BACKGROUND; //Фон
}



void PAGE_Setting(void)
{
  PAGE_Menu(&menu_setting , &item_setting[0], 8);
}


menu_typedef menu_palitra;
item_typedef item_palitra[4] CCMRAM;

void PAGE_init_struct_palitra(void) {

	//
	sprintf(item_setting[0].text, "Назад");
	item_setting[0].field.exit = 1;

    //
	sprintf(item_setting[1].text, "Сохранить");
	//page_item_setting[1].bmp = &bmpSave13232;
	item_setting[1].nameGif = (char*)"save";
	item_setting[1].gif_trigger = ONCE;
	item_setting[1].gif_x = 170;
	item_setting[1].callBackFunc_isClick = &setting_save_click;


    //
	sprintf(item_setting[2].text, "Загрузить");
	//page_item_setting[2].bmp = &bmpProgram3232;

    //
	sprintf(item_setting[3].text, "Яркость");

	//
	sprintf(item_setting[4].text, "USB MSD");
	item_setting[4].callBackFunc_isClick = &PAGE_MSD; //По нажатию

	//
	sprintf(item_setting[5].text, "Палитра");
	item_setting[5].callBackFunc_isClick = &PAGE_Palitra;


	sprintf(item_setting[6].text, "BT Audio");
	item_setting[6].callBackFunc_isClick = &PAGE_BT_Audio;


	sprintf(item_setting[7].text, "Wiget");
	item_setting[7].callBackFunc_isClick = &PAGE_Volume;


	for(int i = 0; i < 8 ; i++)
	{
		item_setting[i].text_color = -1;
	}

	//Описание как рендерить меню
	menu_setting.item_count   = 6;
	menu_setting.item_height  = 40;
	menu_setting.item_start_y = 0;
	menu_setting.font = Roboto_Medium_en_ru_30; //&_acRoboto_Medium_en_ru_30[0];
	menu_setting.field.verticalScroll = 1; //Включит скролл
	menu_setting.items = item_setting;
	menu_setting.ColorBackground = palitra_COLOR_BACKGROUND; //Фон
}





