/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2022-05-11

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f0xx.h"
void init_gpio() {
RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
}

void blinkLed8() {
GPIOC->ODR ^= GPIO_ODR_8;
}
void TIM6_DAC_IRQHandler(void) {
	TIM6->SR &= ~TIM_SR_UIF;

	blinkLed8();
}

void blinkLed9() {
if(TIM6->CNT>2000){
	GPIOC->ODR ^= GPIO_ODR_9;
return;
}
GPIOC->BSRR = GPIO_BSRR_BS_9;
}
 void init_TIM6()
{
	 RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	 TIM6->ARR |= 4000-1;
	 TIM6->PSC |= 1000-1;

	 TIM6->DIER |= TIM_DIER_UIE;

	 NVIC_SetPriority(TIM6_DAC_IRQn, 8);
	 	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	 TIM6->CR1 |=TIM_CR1_CEN;
}
 int  main(void)
{
init_gpio();
init_TIM6();
		while (1)
		{
			blinkLed9();
			}

	  }

void ADC_init() {
	int count = 0;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // ?????????? ???????????? ???

	RCC->CR2 |= RCC_CR2_HSI14ON;
//		RCC->CIR |= RCC_CIR_HSI14RDYIE;
	while((RCC->CR2 & RCC_CR2_HSI14RDY) != RCC_CR2_HSI14RDY) {
		++count;
	}

	ADC1->CHSELR |= (uint32_t)(ADC_CHSELR_CHSEL2|ADC_CHSELR_CHSEL6);
	ADC1->SMPR |= ADC_SMPR_SMP;	//minimal freq conversion
//	ADC1->CFGR1 |= ADC_CFGR1_CONT;	//continuous conversion
	ADC1->CFGR1 |= ADC_CFGR1_DISCEN;
	ADC1->CFGR1 |= ADC_CFGR1_EXTEN_0;	//rising
	ADC1->CFGR1 |= ADC_CFGR1_EXTSEL_2;

	ADC1->IER |= ADC_IER_EOCIE;

	NVIC_SetPriority(ADC1_COMP_IRQn, 6);  // ??????????
	NVIC_EnableIRQ(ADC1_COMP_IRQn);

	ADC1->CR |= ADC_CR_ADEN;	//???????? ???
	ADC1->CR |= ADC_CR_ADSTART;	//???????? ?????????????? ???
}





