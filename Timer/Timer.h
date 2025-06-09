//
// Created by alizayan684 on 2025-06-08.
//

#ifndef TIMER_H
#define TIMER_H

#include "Std_Types.h"
#include "Timer_Private.h"

/**
 * Initializes TIM2 for input capture mode on Channel 1 (PA0)
 * Configures the timer with 1MHz clock (1us resolution)
 */
void TIM2_InputCapture_Init(void);

/**
 * Checks if a capture event has been detected
 * @return 1 if capture event detected, 0 otherwise
 */
uint8 TIM2_CaptureEvent_Detected(void);

/**
 * Gets the captured timer value
 * @return The timer value captured at the rising edge
 */
uint32 TIM2_GetCaptureValue(void);

/**
 * Clears the capture flag
 */
void TIM2_ClearCaptureFlag(void);

/**
 * Measures the frequency of the input signal
 * @return Frequency in Hz
 */
uint32 TIM2_MeasureFrequency(void);

/**
 * Measures the period of the input signal
 * @return Period in microseconds
 */
uint32 TIM2_MeasurePeriod(void);

#endif //TIMER_H