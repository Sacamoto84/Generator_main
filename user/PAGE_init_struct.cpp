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
	page_item_generator[INDEX_CH1_EN].text_color = -1;
	page_item_generator[INDEX_CH1_EN].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_EN].callBackFunc_isClick = &PAGE_generator_CH1_CH_EN_switch;

	//page_item_generator[1].text = (char*) "CH1 1000Hz";
	page_item_generator[INDEX_CH1_FR].text_color = -1;
	page_item_generator[INDEX_CH1_FR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_FR].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;

	//page_item_generator[2].text = (char*) "CH1 SINUS";
	page_item_generator[INDEX_CH1_CR].text_color = -1;
	page_item_generator[INDEX_CH1_CR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_CR].callBackFunc_isClick = &PAGE_generator_select_modulation;

	//page_item_generator[3].text = (char*) "AM Enable";
	page_item_generator[INDEX_CH1_AM_EN].text_color = -1;
	page_item_generator[INDEX_CH1_AM_EN].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_AM_EN].callBackFunc_isClick = &PAGE_generator_CH1_AM_EN_switch;

	//page_item_generator[4].text = (char*) "AM-CHARP";
	page_item_generator[INDEX_CH1_AM_MOD].text_color = -1;
	page_item_generator[INDEX_CH1_AM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_AM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	//page_item_generator[5].text = (char*) "AM-10.4 Hz";
	page_item_generator[INDEX_CH1_AM_FR].text_color = -1;
	page_item_generator[INDEX_CH1_AM_FR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_AM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;

	//page_item_generator[6].text = (char*) "FM Enable";
	page_item_generator[INDEX_CH1_FM_EN].text_color = -1;
	page_item_generator[INDEX_CH1_FM_EN].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_FM_EN].callBackFunc_isClick  = &PAGE_generator_CH1_FM_EN_switch;

	//page_item_generator[7].text = (char*) "FM-Base 2500";
	page_item_generator[INDEX_CH1_FM_BASE].text_color = -1;
	page_item_generator[INDEX_CH1_FM_BASE].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_FM_BASE].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;

	//page_item_generator[8].text = (char*) "FM-Div  200";
	page_item_generator[INDEX_CH1_FM_DEV].text_color = -1;
	page_item_generator[INDEX_CH1_FM_DEV].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_FM_DEV].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;

	//page_item_generator[9].text = (char*) "FM-SINus ";
	page_item_generator[INDEX_CH1_FM_MOD].text_color = -1;
	page_item_generator[INDEX_CH1_FM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_FM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	//page_item_generator[10].text = (char*) "FM-12.5 Hz ";
	page_item_generator[INDEX_CH1_FM_FR].text_color = -1;
	page_item_generator[INDEX_CH1_FM_FR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH1_FM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;


	//page_item_generator[11].text = (char*) "--------------";
	page_item_generator[INDEX_SEPARATOR].text_color = tft.RGB565(0, 0, 255);
	page_item_generator[INDEX_SEPARATOR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_SEPARATOR].text_color = -1;


	//page_item_generator[12].text = (char*) "CH2 EN";
	page_item_generator[INDEX_CH2_EN].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_EN].text_color = -1;
	page_item_generator[INDEX_CH2_EN].callBackFunc_isClick = &PAGE_generator_CH2_CH_EN_switch;

	//page_item_generator[13].text = (char*) "CR 1000Hz";
	page_item_generator[INDEX_CH2_FR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_FR].text_color = -1;
	page_item_generator[INDEX_CH2_FR].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;

	//page_item_generator[14].text = (char*) "CR SINUS";
	page_item_generator[INDEX_CH2_CR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_CR].text_color = -1;
	page_item_generator[INDEX_CH2_CR].callBackFunc_isClick = &PAGE_generator_select_modulation;

	//page_item_generator[15].text = (char*) "AM EN";
	page_item_generator[INDEX_CH2_AM_EN].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_AM_EN].text_color = -1;
	page_item_generator[INDEX_CH2_AM_EN].callBackFunc_isClick = &PAGE_generator_CH2_AM_EN_switch;

	//page_item_generator[16].text = (char*) "--CHARP";
	page_item_generator[INDEX_CH2_AM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_AM_MOD].text_color = -1;
	page_item_generator[INDEX_CH2_AM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	//page_item_generator[17].text = (char*) "AM 10.4 Hz";
	page_item_generator[INDEX_CH2_AM_FR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_AM_FR].text_color = -1;
	page_item_generator[INDEX_CH2_AM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;


	//page_item_generator[18].text = (char*) "FM Base 2500";
	page_item_generator[INDEX_CH2_FM_EN].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_FM_EN].text_color = -1;
	page_item_generator[INDEX_CH2_FM_EN].callBackFunc_isClick  = &PAGE_generator_CH2_FM_EN_switch;

	//page_item_generator[19].text = (char*) "--Div 200";
	page_item_generator[INDEX_CH2_FM_BASE].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_FM_BASE].text_color = -1;
	page_item_generator[INDEX_CH2_FM_BASE].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;

	//page_item_generator[20].text = (char*) "--SIN ";
	page_item_generator[INDEX_CH2_FM_DEV].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_FM_DEV].text_color = -1;
	page_item_generator[INDEX_CH2_FM_DEV].callBackFunc_isClick = &PAGE_generator_encoder_block_switch;

	//page_item_generator[21].text = (char*) "--12.5 Hz ";
	page_item_generator[INDEX_CH2_FM_MOD].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_FM_MOD].text_color = -1;
	page_item_generator[INDEX_CH2_FM_MOD].callBackFunc_isClick  = &PAGE_generator_select_modulation;

	page_item_generator[INDEX_CH2_FM_FR].callBackFunc_isHolded = &PAGE_Setting;
	page_item_generator[INDEX_CH2_FM_FR].text_color = -1;
	page_item_generator[INDEX_CH2_FM_FR].callBackFunc_isClick  = &PAGE_generator_encoder_block_switch;

	//Описание как рендерить меню
	//page_generator.item_count   = 10;
	//page_generator.item_height  = 24;
	page_generator.item_count   = 6;
	page_generator.item_height  = 40;
	page_generator.item_start_y = 0;
	//page_generator.font =  &_acRoboto_Medium_en_ru_18[0];
	page_generator.font =  &_acRoboto_Medium_en_ru_30[0];
	page_generator.preCallBackFunc = &prePageGenerator;
    page_generator.item_text_delta_y = -3;
    page_generator.verticalScroll = 1; //Включит скролл
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
	sprintf(page_item_setting[0].text, "Назад");
	page_item_setting[0].exit = 1;
	page_item_setting[0].text_color = -1;
    //
	sprintf(page_item_setting[1].text, "Сохранить");
	page_item_setting[1].bmp = &bmpSave13232;
	page_item_setting[1].text_color = -1;
    //
	sprintf(page_item_setting[2].text, "Загрузить");
	page_item_setting[2].bmp = &bmpProgram3232;
	page_item_setting[2].text_color = -1;
    //
	sprintf(page_item_setting[3].text, "Яркость");
	page_item_setting[3].text_color = -1;
	//
	sprintf(page_item_setting[4].text, "USB MSD");
	page_item_setting[4].callBackFunc_isClick = &PAGE_MSD; //По нажатию
	page_item_setting[4].text_color = -1;
	//
	sprintf(page_item_setting[5].text, "Палитра");
	page_item_setting[5].callBackFunc_isClick = &PAGE_Palitra;
	page_item_setting[5].text_color = -1;

	//Описание как рендерить меню
	page_setting.item_count   = 6;
	page_setting.item_height  = 40;
	page_setting.item_start_y = 0;

	page_setting.font = &_acRoboto_Medium_en_ru_30[0];

}

void PAGE_Setting(void)
{
  PAGE_Menu(&page_setting , &page_item_setting[0], 6);
}



