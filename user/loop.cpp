#include <Page.h>
#include "main.h"

#include "stdio.h"

#define NUM_OF(x) (sizeof(x)/sizeof(x[0]))

#include "global_define.h"

#include "TimesNRCyr16.h"
#include "IniFile.h"
#include "BLE_Commands.h"

#include "usart.h"

extern void PAGE_Palitra0_15(void);
extern void taskCLI_setup(void);

char str[256] CCMRAM;

void illegal_instruction_execution(void) {
	void (*func_name) (void);
	func_name = (void (*)())0x77777777;
	func_name();
}

void setup(void) {

	LOG_init();

	TimerDWT.init();
	TimerT5.init(&htim5);

#ifdef USE_CLI
	  taskCLI_setup();

	  USART3->CR1 |=  USART_CR1_RXNEIE; //Interupt RX
	  USART3->CR3 |=  USART_CR3_DMAT;
#endif

	HAL_Delay(1000);

	__HAL_SPI_DISABLE(&hspi1);
	SPI1->CR1 |= (0x1UL << (5U));
	__HAL_SPI_ENABLE(&hspi1);

	tft.init(&LCD_0);

    __HAL_SPI_DISABLE(&hspi1);
    SPI1->CR1 &= ~(0x1UL << (5U));
    __HAL_SPI_ENABLE(&hspi1);

	tft.ST77XX_Update_MADCTL();

#ifdef USE_GEN
	Gen.Init();//Инициализация генератора
#endif

	PAGE_init_palitra();

	gfxfont.init(&tft);

	tft.setResStartAdress(0x08020000); //Установим начало ресурсов







	//gfxfont.setFont(&FreeMonoBold12pt7b);
	//gfxfont.setFont(&FreeSansBold12pt7b);

	//gfxfont.setFont(&DejaVu_Sans_Mono_Bold_24);

	//////gfxfont.setFont(&FreeMono14pt8b);

	//gfxfont.setFont(&CourierCyr16pt8b);



	//gfxfont.setFont(&CourierCyr14pt8b);
	//gfxfont.setFont(&Cooper18pt8b);



	tft.SetFontColor(4, 14);

	//tft.Font_Smooth_Load(&_acJetBrainsMono_Bold_en_ru_32[0]);

	//Инициализация структур для экранов
	PAGE_init_struct_generator(); //Картинка генератора
	PAGE_init_struct_setting();   //Настройка


	//tft.Font_Smooth_Load(&_acRoboto_Medium_en_ru_30[0]);
	//tft.Font_Smooth_Load(&_acJetBrainsMono_Medium_en_ru_30[0]);




	//HardFault_Handler();

	//illegal_instruction_execution();

	PAGE_Menu( &menu_generator,  &item_generator[0], 23);



	//tft.Font_Smooth_Load(&_acJetBrainsMono_Medium_en_ru_30[0]);
	//PAGE_Palitra0_15();

	//PAGE_Menu( page_setting,  &page_menu[0], NUM_OF(page_menu));

	//tft.GotoXY(0, 20);
	//gfxfont.set_delta_x(0);
	//gfxfont.drawChar('T');
	//gfxfont.Puts((char*)"Hello12345");

	//tft.ST7789_Update();





}


void loop() {



	while (1) {
		//SEGGER_SYSVIEW_Warn("loop\n");
		//HAL_Delay(10000);
		//tft.ST7789_UpdateDMA4bit();

		//BLE_Task();

		//LED.run();

		//	i = (uint32_t) HAL_ADC_GetValue(&hadc1);
		//	Vbus = i / 4096.0F * 3.3F * 3.95F/2.65F ;

		//	__WFI();
		//
	}
}

extern "C" void main_cpp(void) {
	setup();
	loop();
}

extern "C" void DMA1_Stream5_IRQHandler(void)
{
	SEGGER_SYSVIEW_RecordEnterISR(); //SEGGER SW

#ifdef USE_GEN
	//Other_Run_Tick = TimerT5.End(); //Получаем время работы без тиков
	DMA_Sum_Tick   = Other_Run_Tick + DMA_Run_Tick;
	DMA_zagruzka = (float)DMA_Run_Tick / (float)DMA_Sum_Tick * 100.0F;

	//DMA_Run_us   = DMA_Run_Tick / TimerT5.tickToUs;
	//Other_Run_us = Other_Run_Tick / TimerT5.tickToUs;
	//DMA_Sum_us   = DMA_Sum_Tick / TimerT5.tickToUs;

	//TimerT5.Start();

	if (DMA1_Stream5->CR & DMA_SxCR_CT)
	{
		Gen.DMA_Buffer_Current = 0;
	    Gen.syg_update(0);
	}
	else
	{
		Gen.DMA_Buffer_Current = 1;
	    Gen.syg_update(1);
	}
	HAL_DMA_IRQHandler(&hdma_dac1);

	//DMA_Run_Tick = TimerT5.End(); //Получили тики работы
	//TimerT5.Start();

#endif

	SEGGER_SYSVIEW_RecordExitISR(); //SEGGER SW
}


