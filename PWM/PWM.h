//
// Created by Marcilino on 6/8/2025.
//

#ifndef PWM_H
#define PWM_H

#include "Std_Types.h"
#include "stm32f401xe.h"
#include "Gpio.h"

// PWM Configuration
#define PWM_TIMER TIM1
#define PWM_CHANNEL 1
#define PWM_PIN_PORT GPIO_A
#define PWM_PIN 8 // PA8 for TIM1_CH1
#define PWM_AF 1 // Alternate function 1 for TIM1
#define PWM_FREQ 1000 // 1 kHz PWM frequency
#define PWM_PERIOD (16000000 / PWM_FREQ) - 1 // ARR value for 16 MHz clock

void PWM_Init(void);
void PWM_SetDutyCycle(uint16 adc_value); // Input ADC value (0–4095)
uint8 PWM_GetDutyCyclePercentage(void); // Return current duty cycle as percentage

#endif //PWM_H
