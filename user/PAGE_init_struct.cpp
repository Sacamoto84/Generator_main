#include "Page.h"
#include "global_define.h"

#include "SEGGER.h"
#include "SEGGER_SYSVIEW.h"
#include "stdio.h"

void PAGE_Setting(void);

extern Bitmap bmpProgram3232;
extern Bitmap bmpSave13232;
extern Bitmap bmpGlass240240;
extern Bitmap bmpBackground240240;
extern Bitmap bmp_ac889727_3232;
extern Bitmap bmp_on_3232;
extern Bitmap bmp_off_3232;



void PAGE_init_struct_generator(void)
{
	palitra[16] = tft.RGB565(0, 130, 200);
	palitra[17] = tft.RGB565(1, 28, 105);
	palitra[18] = tft.RGB565(2, 78, 153);
	palitra[19] = tft.RGB565(2, 166, 255);
	palitra[20] = tft.RGB565(255, 200, 11);
	palitra[21] = tft.RGB565(5, 56, 122);
	palitra[22] = tft.RGB565(234, 236, 255);
	palitra[23] = tft.RGB565(15, 91, 169);


	//page_item_generator[0].text = (char*) "CH1 ENABLE";
	item_generator[INDEX_CH1_EN].text_color = -1;
	item_generator[INDEX_CH1_EN].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_EN].callBackFunc_isClick = &PAGE_generator_CH1_CH_EN_switch;
	//page_item_generator[INDEX_CH1_EN].nameGif = (char*)"serv24";
	//page_item_generator[INDEX_CH1_EN].resid = 6;
	item_generator[INDEX_CH1_EN].preCallBackFunc = &generator_pre_CH1_EN;



	//page_item_generator[1].text = (char*) "CH1 1000Hz";
	item_generator[INDEX_CH1_FR].text_color = -1;
	item_generator[INDEX_CH1_FR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_FR].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FR].nameGif = (char*)"serv";
	item_generator[INDEX_CH1_FR].preCallBackFunc = &generator_pre_CH1_FR;



	//page_item_generator[2].text = (char*) "CH1 SINUS";
	item_generator[INDEX_CH1_CR].text_color = -1;
	item_generator[INDEX_CH1_CR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_CR].callBackFunc_isClick = &PAGE_generator_select_modulation;
	item_generator[INDEX_CH1_CR].nameGif = (char*)"usb";
	item_generator[INDEX_CH1_CR].resid_first   = 6;



	//page_item_generator[3].text = (char*) "AM Enable";
	item_generator[INDEX_CH1_AM_EN].text_color = -1;
	item_generator[INDEX_CH1_AM_EN].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_AM_EN].callBackFunc_isClick = &PAGE_generator_CH1_AM_EN_switch;
	item_generator[INDEX_CH1_AM_EN].nameGif = (char*)"serv";
	//page_item_generator[INDEX_CH1_AM_EN].resid   = 4;
	item_generator[INDEX_CH1_AM_EN].preCallBackFunc = &generator_pre_CH1_AM_EN;


	//page_item_generator[4].text = (char*) "AM-CHARP";
	item_generator[INDEX_CH1_AM_MOD].text_color = -1;
	item_generator[INDEX_CH1_AM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_AM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;
	item_generator[INDEX_CH1_AM_MOD].nameGif = (char*)"Q12";
	//page_item_generator[INDEX_CH1_AM_MOD].resid   = 5;
	//item_generator[INDEX_CH1_AM_MOD].menu = &menu_generator;



	//page_item_generator[5].text = (char*) "AM-10.4 Hz";
	item_generator[INDEX_CH1_AM_FR].text_color = -1;
	item_generator[INDEX_CH1_AM_FR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_AM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	//item_generator[INDEX_CH1_AM_FR].menu = &menu_generator;
	item_generator[INDEX_CH1_AM_FR].preCallBackFunc = &generator_pre_CH1_AM_FR;



	//page_item_generator[6].text = (char*) "FM Enable";
	item_generator[INDEX_CH1_FM_EN].text_color = -1;
	item_generator[INDEX_CH1_FM_EN].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_FM_EN].callBackFunc_isClick  = &PAGE_generator_CH1_FM_EN_switch;
	item_generator[INDEX_CH1_FM_EN].preCallBackFunc = &generator_pre_CH1_FM_EN;

	//page_item_generator[7].text = (char*) "FM-Base 2500";
	item_generator[INDEX_CH1_FM_BASE].text_color = -1;
	item_generator[INDEX_CH1_FM_BASE].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_FM_BASE].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FM_BASE].preCallBackFunc = &generator_pre_CH1_FM_BASE;

	//page_item_generator[8].text = (char*) "FM-Div  200";
	item_generator[INDEX_CH1_FM_DEV].text_color = -1;
	item_generator[INDEX_CH1_FM_DEV].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_FM_DEV].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FM_DEV].preCallBackFunc = &generator_pre_CH1_FM_DEV;




	//page_item_generator[9].text = (char*) "FM-SINus ";
	item_generator[INDEX_CH1_FM_MOD].text_color = -1;
	item_generator[INDEX_CH1_FM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_FM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;
	//item_generator[INDEX_CH1_FM_MOD].menu = &menu_generator;

	//page_item_generator[10].text = (char*) "FM-12.5 Hz ";
	item_generator[INDEX_CH1_FM_FR].text_color = -1;
	item_generator[INDEX_CH1_FM_FR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH1_FM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH1_FM_FR].preCallBackFunc = &generator_pre_CH1_FM_FR;



	//page_item_generator[11].text = (char*) "--------------";
	item_generator[INDEX_SEPARATOR].text_color = tft.RGB565(0, 0, 255);
	item_generator[INDEX_SEPARATOR].callBackFunc_isHolded = &PAGE_Setting;
	//page_item_generator[INDEX_SEPARATOR].text_color = -1;
	//item_generator[INDEX_SEPARATOR].menu = &menu_generator;


	//page_item_generator[12].text = (char*) "CH2 EN";
	item_generator[INDEX_CH2_EN].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_EN].callBackFunc_isClick = &PAGE_generator_CH2_CH_EN_switch;
	item_generator[INDEX_CH2_EN].preCallBackFunc = &generator_pre_CH1_EN;

	//page_item_generator[13].text = (char*) "CR 1000Hz";
	item_generator[INDEX_CH2_FR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_FR].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FR].preCallBackFunc = &generator_pre_CH2_FR;
	//item_generator[INDEX_CH2_FR].menu = &menu_generator;

	//page_item_generator[14].text = (char*) "CR SINUS";
	item_generator[INDEX_CH2_CR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_CR].callBackFunc_isClick = &PAGE_generator_select_modulation;
	//item_generator[INDEX_CH2_CR].menu = &menu_generator;

	//page_item_generator[15].text = (char*) "AM EN";
	item_generator[INDEX_CH2_AM_EN].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_AM_EN].callBackFunc_isClick = &PAGE_generator_CH2_AM_EN_switch;
	item_generator[INDEX_CH2_AM_EN].preCallBackFunc = &generator_pre_CH2_AM_EN;


	//page_item_generator[16].text = (char*) "--CHARP";
	item_generator[INDEX_CH2_AM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_AM_MOD].text_color = -1;
	item_generator[INDEX_CH2_AM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	//page_item_generator[17].text = (char*) "AM 10.4 Hz";
	item_generator[INDEX_CH2_AM_FR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_AM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_AM_FR].preCallBackFunc = &generator_pre_CH2_AM_FR;

	//page_item_generator[18].text = (char*) "FM Base 2500";
	item_generator[INDEX_CH2_FM_EN].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_FM_EN].callBackFunc_isClick  = &PAGE_generator_CH2_FM_EN_switch;
	item_generator[INDEX_CH2_FM_EN].preCallBackFunc = &generator_pre_CH2_FM_EN;

	//page_item_generator[19].text = (char*) "--Div 200";
	item_generator[INDEX_CH2_FM_BASE].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_FM_BASE].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FM_BASE].preCallBackFunc = &generator_pre_CH2_FM_BASE;


	//page_item_generator[20].text = (char*) "--SIN ";
	item_generator[INDEX_CH2_FM_DEV].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_FM_DEV].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FM_DEV].preCallBackFunc = &generator_pre_CH2_FM_DEV;


	//page_item_generator[21].text = (char*) "--12.5 Hz ";
	item_generator[INDEX_CH2_FM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_FM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;
	//item_generator[INDEX_CH2_FM_MOD].menu = &menu_generator;

	item_generator[INDEX_CH2_FM_FR].callBackFunc_isHolded = &PAGE_Setting;
	item_generator[INDEX_CH2_FM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;
	item_generator[INDEX_CH2_FM_FR].preCallBackFunc = &generator_pre_CH2_FM_FR;

	//Описание как рендерить меню
	//page_generator.item_count   = 10;
	//page_generator.item_height  = 24;
	menu_generator.item_count   = 6;
	menu_generator.item_height  = 40;
	menu_generator.item_start_y = 0;
	//page_generator.font =  &_acRoboto_Medium_en_ru_18[0];


	menu_generator.font = FontId0; //&_acRoboto_Medium_en_ru_30[0];
	menu_generator.preCallBackFunc = &prePageGenerator;
    menu_generator.item_text_delta_y = -3;
    menu_generator.field.verticalScroll = 1; //Включит скролл

    menu_generator.items = &item_generator[0];
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
	item_setting[0].text_color = -1;
    //
	sprintf(item_setting[1].text, "Сохранить");
	//page_item_setting[1].bmp = &bmpSave13232;
	item_setting[1].text_color = -1;
    //
	sprintf(item_setting[2].text, "Загрузить");
	//page_item_setting[2].bmp = &bmpProgram3232;
	item_setting[2].text_color = -1;
    //
	sprintf(item_setting[3].text, "Яркость");
	item_setting[3].text_color = -1;
	//
	sprintf(item_setting[4].text, "USB MSD");
	item_setting[4].callBackFunc_isClick = &PAGE_MSD; //По нажатию
	item_setting[4].text_color = -1;
	//
	sprintf(item_setting[5].text, "Палитра");
	item_setting[5].callBackFunc_isClick = &PAGE_Palitra;
	item_setting[5].text_color = -1;

	sprintf(item_setting[6].text, "BT Audio");
	item_setting[6].callBackFunc_isClick = &PAGE_BT_Audio;
	item_setting[6].text_color = -1;

	sprintf(item_setting[7].text, "Wiget");
	item_setting[7].callBackFunc_isClick = &PAGE_Volume;
	item_setting[7].text_color = -1;

	//Описание как рендерить меню
	menu_setting.item_count   = 6;
	menu_setting.item_height  = 40;
	menu_setting.item_start_y = 0;

	menu_setting.font = Roboto_Medium_en_ru_30; //&_acRoboto_Medium_en_ru_30[0];

	menu_setting.field.verticalScroll = 1; //Включит скролл
}

void PAGE_Setting(void)
{
  PAGE_Menu(&menu_setting , &item_setting[0], 8);
}



