//
// Created by Marcilino on 6/8/2025.
//

#ifndef ADC_H
#define ADC_H


#include "Std_Types.h"
#include "stm32f4xx.h"
#include "Gpio.h"
#include "Gpio_Private.h"


/* ADC1 Base Address */
#define MY_ADC1_BASE 0x40012000

/* ADC1 Registers - Corrected by adding pointer dereference */
#define MY_ADC1_SR (*(volatile uint32_t *)(MY_ADC1_BASE + 0x00))
#define MY_ADC1_CR1 (*(volatile uint32_t *)(MY_ADC1_BASE + 0x04))
#define MY_ADC1_CR2 (*(volatile uint32_t *)(MY_ADC1_BASE + 0x08))
#define MY_ADC1_SMPR1 (*(volatile uint32_t *)(MY_ADC1_BASE + 0x0C))
#define MY_ADC1_SMPR2 (*(volatile uint32_t *)(MY_ADC1_BASE + 0x10))
#define MY_ADC1_SQR1 (*(volatile uint32_t *)(MY_ADC1_BASE + 0x2C))
#define MY_ADC1_SQR3 (*(volatile uint32_t *)(MY_ADC1_BASE + 0x34))
#define MY_ADC1_DR (*(volatile uint32_t *)(MY_ADC1_BASE + 0x4C))

/* ADC Bit Fields */
#define MY_ADC_CR2_ADON (1 << 0)
#define MY_ADC_CR2_SWSTART (1 << 30)
#define MY_ADC_SR_EOC (1 << 1)

void ADC_Init(void);
uint16 ADC_ReadChannel(uint8 channel);




#endif //ADC_H
