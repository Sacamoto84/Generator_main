#ifndef __GLOBAL_DEFINE_H
#define __GLOBAL_DEFINE_H

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
#include "adc.h"                //
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
//////////////////////////////////

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

   //char * value;
   //int8_t value_dx;
   //int8_t value_dy;

   uint8_t bitmap_always_on;
   uint8_t exit;

   //uint8_t select;

   void (*callBackFunc_isClick)  (void);
   void (*callBackFunc_isHolded) (void);
   void (*callBackFunc_isDouble) (void);

   Bitmap *bmp;  //Картинка 32x32

   int32_t text_color = -1; //Цвет текста -1 использовать значения по умолчанию

 } PAGE_Menu_item_typedef;

 /*********************************/

 typedef struct
 {
   //Блок инициализации
   uint8_t item_count;    //Количество отображаемых строк
   uint8_t item_height;   //Высота одной строки
   uint8_t item_start_y;  //Координата Y начала списка

   int8_t  item_text_delta_x;  //Смещение текста по X
   int8_t  item_text_delta_y;  //Смещение текста по Y

   const unsigned char * font; //Используеммый шрифт


   //Callback
   void (*preCallBackFunc)  (void);
   void (*postCallBackFunc) (void);

   //char * title;

   //Enable
   uint8_t verticalScroll; //1-использовать вертикальный скролл
   uint8_t encoder_block;  //Блокировка энкодера


   uint32_t temp;
   uint32_t tempf;


   uint32_t index;
   int window_start;
   int window_end;
   int max_item;

   int count_item; //Максимальное количество элементов

   PAGE_Menu_item_typedef * items;

 } PAGE_Menu_config_typedef;

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

extern uint16_t palitra[256] CCMRAM;

extern GButton KEY;

extern uint8_t u8Volume;
extern float    fVolume;

extern uTFT_LCD_t LCD_0;

extern PAGE_Menu_config_typedef page_generator;
extern PAGE_Menu_config_typedef page_setting;

extern PAGE_Menu_item_typedef page_item_setting[]   CCMRAM;
extern PAGE_Menu_item_typedef page_item_generator[] CCMRAM;

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
