#include "scripting.h"
#include "HiSpeedDWT.h"

Scripting script;

extern HiSpeedDWT TimerDWT;
extern HiSpeedDWT TimerT5;

int i;

//Каждые 10ms
extern "C" void TIM7_IRQHandler(void) {
	script.run();
	HAL_TIM_IRQHandler(&htim7);
}

