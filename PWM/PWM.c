//
// Created by Marcilino on 6/8/2025.
//
#include "PWM.h"

void PWM_Init(void) {
    // 1. Enable TIM1 and GPIOA clocks
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;   // Enable TIM1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIOA clock

    // 2. Configure PA8 as alternate function for TIM1_CH1
    Gpio_Init(PWM_PIN_PORT, PWM_PIN, GPIO_AF, GPIO_PUSH_PULL);
    GPIOA->AFR[1] |= (PWM_AF << ((PWM_PIN - 8) * 4)); // Set AF1 for PA8

    // 3. Configure TIM1 for PWM mode
    PWM_TIMER->ARR = PWM_PERIOD;           // Set PWM period (e.g., 1 kHz)
    PWM_TIMER->CCMR1 |= (6 << 4);         // PWM mode 1 for channel 1
    PWM_TIMER->CCER |= (1 << ((PWM_CHANNEL - 1) * 4)); // Enable channel 1 output
    PWM_TIMER->BDTR |= (1 << 15);         // Enable main output
    PWM_TIMER->CR1 |= (1 << 0);           // Enable timer
}

void PWM_SetDutyCycle(uint8 percentage) {
    if (percentage > 100) percentage = 100; // Cap at 100%
    PWM_TIMER->CCR1 = (percentage * PWM_PERIOD) / 100; // Set duty cycle
}