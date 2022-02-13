/*
 * dma2_s3_spi1.cpp
 *
 *  Created on: 19 но€б. 2021 г.
 *      Author: Ivan
 */

#include "main.h"
#include "TFT.h"
#include "dma.h"

extern DMA_HandleTypeDef hdma_spi1_tx;
extern TFT tft CCMRAM;

extern "C" void DMA2_Stream3_IRQHandler(void)
{

	if (DMA2->LISR & DMA_LISR_TCIF3)
		      tft.DMA_TX_Complete = 1;

	if (DMA2->LISR & DMA_LISR_FEIF3)
			      tft.DMA_TX_Complete = 1;

  HAL_DMA_IRQHandler(&hdma_spi1_tx);
}


