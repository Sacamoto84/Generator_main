#include "global_define.h"

Encoder_typedef Encoder CCMRAM;


extern char str1[60];

extern int8_t PAGE_Generator_Encoder_index;

#define SEGGER

//Правый энкодер
extern "C" void TIM2_IRQHandler(void)
{
	#if defined(SEGGER)
	  SEGGER_SYSVIEW_RecordEnterISR();
	#endif
	
	if (TIM2->CR1 & TIM_CR1_DIR)
	{  
	  Encoder.Right = 1;
	}
	else{
	  Encoder.Left  = 1;
	}
	
	#if defined(SEGGER)
	  SEGGER_SYSVIEW_RecordExitISR();
	#endif
	
  HAL_TIM_IRQHandler(&htim2);
}
