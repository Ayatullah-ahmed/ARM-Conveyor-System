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
    GPIOC_MODER &= ~(0x3 << (0 * 2));    // Clear MODER0 bits
    GPIOC_MODER |= (0x3 << (0 * 2));     // Set PC0 to analog mode (MODER0 = 11)

    // 3. Configure ADC prescaler (PCLK2/4 for safe clock range)
    ADC->CCR |= (1 << 16);               // ADC prescaler = PCLK2/4

    // 4. Configure ADC settings
    ADC1_CR2 = 0;                        // Clear control register
    ADC1_SQR3 = 10;                      // Set channel 10 in regular sequence
    ADC1_SMPR2 |= (7 << 0);              // Max sample time (480 cycles) for channel 10

    // 5. Enable ADC and wait for stabilization
    ADC1_CR2 |= ADC_CR2_ADON;            // Enable ADC
    for (volatile uint32 i = 0; i < 1000; i++); // Stabilization delay
}

uint16 ADC_ReadChannel(uint8 channel) {
    // Validate channel
    if (channel > 18) return 0;          // Return 0 for invalid channel

    // Select channel
    ADC1_SQR3 = channel;

    // Start conversion
    ADC1_CR2 |= ADC_CR2_SWSTART;

    // Wait for conversion with timeout
    uint32 timeout = 100000;
    while (!(ADC1_SR & ADC_SR_EOC) && timeout--) {
        if (timeout == 0) return 0;      // Timeout error
    }

    // Read and return result
    uint16 result = (uint16)(ADC1_DR & 0xFFFF);
    ADC1_SR &= ~ADC_SR_EOC;             // Clear EOC flag
    return result;
}

uint8 ADC_ValueToPercentage(uint16 adc_value) {
    // Map 12-bit ADC value (0–4095) to 0–100%
    return (uint8)((adc_value * 100UL) / 4095);
}