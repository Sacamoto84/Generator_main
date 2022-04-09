#ifndef __GLOBAL_DEFINE_H
#define __GLOBAL_DEFINE_H

//Если нужно использовать CLI
//#define USE_CLI
#define USE_GEN
//#define USE_CLI_GEN
//#define USE_CLI_LCD

//COLOR
//#define COLOR_TEXT_SELECT    tft.RGB565(255, 200, 11)   //Цвет текста выбранной строки
//#define COLOR_TEXT_DEFAULT   tft.RGB565(234, 236, 255)  //Цвет текста по умолчанию
//#define COLOR_TEXT_DISABLE   tft.RGB565(128, 128, 128)  // Текст отключенного текста

//#define COLOR_RECTAGLE       tft.RGB565(2, 78, 153)     // Текст выделенной строки
//#define COLOR_BACKGROUND     tft.RGB565(0, 0, 16)       //tft.RGB565(0, 7, 43)   // Фон

//#define COLOR_TEXT_SELECT    tft.RGB565(6, 17, 60)   //Цвет текста выбранной строки
//#define COLOR_RECTAGLE       tft.RGB565(255, 140, 50)     // Текст выделенной строки
//#define COLOR_BACKGROUND     tft.RGB565(6, 17, 60)       //tft.RGB565(0, 7, 43)   // Фон

#define COLOR_TEXT_DEFAULT   tft.RGB565(229, 229, 229)  //Цвет текста по умолчанию         100
#define COLOR_TEXT_SELECT    tft.RGB565(16, 16, 16)        //Цвет текста выбранной строки     101
#define COLOR_TEXT_DISABLE   tft.RGB565(128, 128, 128)  // Текст отключенного текста       102
#define COLOR_RECTAGLE       tft.RGB565(255, 140, 50)   // Текст выделенной строки         103
#define COLOR_BACKGROUND     tft.RGB565(0, 0, 7)        //tft.RGB565(0, 7, 43)   // Фон    104

#define palitra_COLOR_TEXT_DEFAULT   palitra[100]  //Цвет текста по умолчанию         100
#define palitra_COLOR_TEXT_SELECT    palitra[101]         //Цвет текста выбранной строки     101
#define palitra_COLOR_TEXT_DISABLE   palitra[102]   // Текст отключенного текста       102
#define palitra_COLOR_RECTAGLE       palitra[103]    // Текст выделенной строки         103
#define palitra_COLOR_BACKGROUND     palitra[104]         //tft.RGB565(0, 7, 43)   // Фон    104

//ID Ресурсов
#define Roboto_Medium_en_ru_30 (uint8_t *)(tft.getResAdressFontID(0))
#define Roboto_Medium_en_ru_18 (uint8_t *)(tft.getResAdressFontID(1))









 ///////////////
 //  define
 ///////////////

//Для картинки генератора индексы строк
#define INDEX_CH1_EN      0
#define INDEX_CH1_FR      1
#define INDEX_CH1_CR      2
#define INDEX_CH1_AM_EN   3
#define INDEX_CH1_AM_MOD  4
#define INDEX_CH1_AM_FR   5
#define INDEX_CH1_FM_EN   6
#define INDEX_CH1_FM_BASE 7
#define INDEX_CH1_FM_DEV  8
#define INDEX_CH1_FM_MOD  9
#define INDEX_CH1_FM_FR   10
#define INDEX_SEPARATOR   11
#define INDEX_CH2_EN      12
#define INDEX_CH2_FR      13
#define INDEX_CH2_CR      14
#define INDEX_CH2_AM_EN   15
#define INDEX_CH2_AM_MOD  16
#define INDEX_CH2_AM_FR   17
#define INDEX_CH2_FM_EN   18
#define INDEX_CH2_FM_BASE 19
#define INDEX_CH2_FM_DEV  20
#define INDEX_CH2_FM_MOD  21
#define INDEX_CH2_FM_FR   22

#define NUM_ITEM_GENERETOR   23



//////////////////////////////////
//          include             //
//////////////////////////////////
#include "stm32f4xx_hal.h"	    //
#include "stm32f4xx.h"          //
#include "stm32f4xx_it.h"  	    //
#include "crc.h"                //
#include "dma.h"      	        //
#include "i2c.h"      	        //
#include "spi.h"                //
#include "tim.h"       	  	    //
#include "gpio.h"               //
#include "main.h"          		//
#include "SEGGER.h"     	    //
#include "SEGGER_RTT.h"     	//
#include "SEGGER_RTT_Conf.h"	//
#include "SEGGER_SYSVIEW.h" 	//
#include "GyverButton.h"        //
#include "TFT.h"            	//
#include "Generator.h"          //
#include "gfxfont.h"            //
#include "gfx_fonts_includes.h" //
#include "HiSpeedDWT.h"         //
#include "LOG.h"                //
#include "TFT_gif.h"            //

//////////////////////////////////
extern TFT tft CCMRAM ;
extern uint16_t palitra[256] CCMRAM;
///////////////
//  typedef  //
///////////////

typedef char __attribute__((aligned (4))) char4;

////////////////////
typedef struct    //
{                 //
  uint8_t Left;   //
  uint8_t Right;  //
}Encoder_typedef;//
////////////////////

 typedef struct
 {
   char text [20];

   void (*callBackFunc_isClick)  (void);
   void (*callBackFunc_isHolded) (void);
   void (*callBackFunc_isDouble) (void);
   void (*preCallBackFunc)(uint32_t);

   /////////////////////////////////////////////////////////
   char *     nameGif  = 0;       //Имя гифки
   TFT_gif *      gif  = 0;       //Указатель на гифку
   int8_t  resid_first =-1 ;      //Номер картинки ресурса первый кадр
   int8_t  resid_last  =-1;       //Номер картинки ресурса последний кадр
   ANIMATION_TRIGGERS      gif_trigger;  //Тип анимации
   uint8_t  gif_x;                       //Координата X гифки
   uint8_t*  gif_init_state;              //Для начального значения
   /////////////////////////////////////////////////////////

	struct fieldbite {
	   unsigned  bitmap_always_on : 1 ;
	   unsigned  exit :1;
	   unsigned  disable:1;  //Если 1 то отключен
	} field;

   int32_t text_color = -1; //Цвет текста -1 использовать значения по умолчанию

 } item_typedef;

 /*********************************/

 typedef struct
 {
   //Блок инициализации
   uint8_t item_count;    //Количество отображаемых строк
   uint8_t item_height;   //Высота одной строки
   uint8_t item_start_y;  //Координата Y начала списка
   uint8_t count_item; //Максимальное количество элементов

   int8_t  item_text_delta_x;  //Смещение текста по X
   int8_t  item_text_delta_y;  //Смещение текста по Y

   const unsigned char * font; //Используеммый шрифт

   //Callback
   void (*preCallBackFunc)  (void);
   void (*postCallBackFunc) (void);


   item_typedef * items;

   uint32_t temp;
   uint32_t tempf;

   struct fieldbite
   {
		unsigned verticalScroll :1; //1-использовать вертикальный скролл
		unsigned encoder_block :1;  //Блокировка энкодера
		unsigned needUpdate :1;     //Требование полной перерисовки кадра
		unsigned needRender :1;
   } field;

   uint8_t index;
   uint8_t window_start;
   uint8_t window_end;
   uint8_t max_item;

   uint8_t ii = 0;

   uint16_t ColorBackground; //Цвет фона

   void run(uint8_t i)
   {
	   //Выполняем пре для этого елемента
	   //Создание текста
	   if (items[i].preCallBackFunc) {
		   void (*fcnPtr)(uint32_t) = items[i].preCallBackFunc;
		   fcnPtr(index);
		}


	   if (items[i].field.disable == 0)
	   {
		   //1500us
		   if (items[i].text_color != -1)
			   tft.Font_Smooth_drawStr(9 - 1 + item_text_delta_x, 8 + item_height * (ii % item_count) - 1 + item_start_y + item_text_delta_y, items[i].text, (uint16_t) items[i].text_color);
		   else
			   tft.Font_Smooth_drawStr(9 - 1 + item_text_delta_x, 8 + item_height * (ii % item_count) - 1 + item_start_y + item_text_delta_y, items[i].text, (i == index) ? palitra_COLOR_TEXT_SELECT : palitra_COLOR_TEXT_DEFAULT);
	   }
	   else
		   tft.Font_Smooth_drawStr(9 - 1 + item_text_delta_x, 8 + item_height * (ii % item_count) - 1 + item_start_y + item_text_delta_y, items[i].text, palitra_COLOR_TEXT_DISABLE); //COLOR_TEXT_DISABLE

   }

 } menu_typedef;

 /*********************************/

 //Создается для каждого файла в папке
 typedef struct
 {
 	char  Name[16];    //Имя файла
 	uint8_t  maxFileCount = 0;
 } Dir_File_Info_Array;


 ///////////////
 //  extern
 //////////////

extern HiSpeedDWT TimerDWT;
extern HiSpeedDWT TimerT5;

extern Encoder_typedef Encoder;

extern TIM_HandleTypeDef htim2;



extern GButton KEY;

extern uint8_t u8Volume;
extern float    fVolume;

extern uTFT_LCD_t LCD_0;

extern menu_typedef menu_generator;
extern menu_typedef menu_setting;
extern menu_typedef menu_palitra;

extern item_typedef item_setting[]   CCMRAM;
extern item_typedef item_generator[] CCMRAM;
extern item_typedef item_palitra[] CCMRAM;

extern Dir_File_Info_Array Dir_File_Info[50] CCMRAM; //Массив всех файлов в папке

//Сформировать и отправить текущие настройки
extern void sendStructCHtoHost(unsigned int ch);

extern uint32_t DMA_Run_Tick;
extern uint32_t DMA_Run_us;
extern uint32_t Other_Run_Tick;
extern uint32_t Other_Run_us;
extern uint32_t DMA_Sum_Tick;
extern uint32_t DMA_Sum_us;
extern float    DMA_zagruzka;

#endif
