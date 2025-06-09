//
// Created by Marcilino on 6/8/2025.
//
#include "ADC.h"
#include "stm32f401xe.h"

void ADC_Init(void) {
    // 1. Enable ADC1 and GPIOC clocks
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // Enable ADC1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Enable GPIOC clock

    // 2. Configure PC0 (channel 10) as analog input
    GPIOC->MODER &= ~(0x3 << (0 * 2));   // Clear MODER0 bits
    GPIOC->MODER |= (0x3 << (0 * 2));    // Set PC0 to analog mode (MODER0 = 11)

    // 3. Configure ADC prescaler (PCLK2/4 for safe clock range)
    ADC->CCR &=~ (3 << 16);
    ADC->CCR |= (3 << 16);               // ADC prescaler = PCLK/8 = 10.5MHZ

    // 4. Configure ADC settings
    // MY_ADC1_CR2 = 0;                     // Clear control register
    // MY_ADC1_SQR3 = 10;                   // Set channel 10 in regular sequence

    MY_ADC1_SMPR2 &= ~(0x07 << 0);
    MY_ADC1_SMPR2 |= (2 << 0);           // Max sample time (28 cycles) for channel 10

    MY_ADC1_CR1 &= ~(0x3 << 24);
    MY_ADC1_CR1 |= (0x0 << 24);     // set resolution
    MY_ADC1_CR2 &= ~(0x1 << 11);
    MY_ADC1_CR2 |= (0x0<< 11);     // set allignment

    // 5. Enable ADC and wait for stabilization
    MY_ADC1_CR2 |= MY_ADC_CR2_ADON;      // Enable ADC
    for (volatile uint32 i = 0; i < 1000; i++); // Stabilization delay
}

uint16 ADC_ReadChannel(uint8 channel) {
    // Validate channel
    if (channel > 18) return 0;          // Return 0 for invalid channel
    MY_ADC1_SQR1 &= ~(0xF <<(20));  // total number of conversions = one1

    // Select channel
    MY_ADC1_SQR3 = channel;

    // Start conversion
    MY_ADC1_CR2 |= MY_ADC_CR2_SWSTART;

    // Wait for conversion with timeout
    uint32 timeout = 100000;
    while (!(MY_ADC1_SR & MY_ADC_SR_EOC) && timeout--) {
        if (timeout == 0) return 0;      // Timeout error
    }

    // Read and return result
    uint16 result = (uint16)(MY_ADC1_DR & 0xFFFF);
    //MY_ADC1_SR &= ~MY_ADC_SR_EOC;       // Clear EOC flag
    return result;
}