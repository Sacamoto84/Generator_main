#include "adc.h"
#include <RingAverage.h>
#include <median3.h>
#include <median.h>

#include "SEGGER.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "SEGGER_SYSVIEW.h"

GMedian<32, float> filterVdd CCMRAM;
GMedian<32, float> filterBat CCMRAM;

float Vdd  CCMRAM;
float Vbat CCMRAM;

extern "C" void ADC_IRQHandler(void) {
	SEGGER_SYSVIEW_RecordEnterISR();
	float AD_RES_f;
	AD_RES_f = 3.3F * 1497.0F / HAL_ADC_GetValue(&hadc1) * 3.256 / 3.23972;
	Vdd = filterVdd.filtered(AD_RES_f);
	AD_RES_f = 6.6F * HAL_ADC_GetValue(&hadc2) / 4096 * 4.00 / 4.05 * 3.96/ 3.97;
	Vbat = filterBat.filtered(AD_RES_f);
	HAL_ADC_IRQHandler(&hadc1);	HAL_ADC_IRQHandler(&hadc2);
	SEGGER_SYSVIEW_RecordExitISR();
}
