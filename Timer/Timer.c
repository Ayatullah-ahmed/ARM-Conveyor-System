#include "Timer.h"
#include "Rcc.h"
#include "Gpio.h"
#include "Std_Types.h"
#include "Utils.h"

void TIM2_InputCapture_Init(void) {
    // 1. Enable clock for GPIOA and TIM2
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_TIM2);

    // 2. Configure PA0 as alternate function input for TIM2_CH1
    // For many STM32s, TIM2_CH1 is on AF1
    Gpio_Init(GPIO_A, 0, GPIO_AF, GPIO_AF1);

    // 3. Configure TIM2 for Input Capture on Channel 1 (TI1)
    // CC1S = 01: CC1 channel is configured as input, IC1 is mapped on TI1
    TIM2->CCMR1 |= (1 << 0);

    // 4. Configure to capture on the rising edge (default) and enable capture
    // CC1P=0, CC1NP=0 for rising edge. CC1E=1 to enable capture.
    TIM2->CCER |= (1 << 0);

    // 5. Set prescaler. The Rcc_Init() enables the 16MHz HSI.
    // Timer clock = System Clock / (Prescaler + 1)
    // 1MHz = 16MHz / (15 + 1)
    TIM2->PSC = 15;
    TIM2->ARR = 0xFFFF; // Set auto-reload register to max for 16-bit timer

    // 6. Enable the timer counter
    TIM2->CR1 |= (1 << 0);
}

uint8 TIM2_CaptureEvent_Detected(void) {
    // Check the CC1IF (Capture/Compare 1 Interrupt Flag) in the status register
    return (TIM2->SR & (1 << 1));
}

void TIM2_ClearCaptureFlag(void) {
    // Clear the CC1IF flag by writing 0 to it.
    TIM2->SR &= ~(1 << 1);
}

uint32 TIM2_GetCaptureValue(void) {
    // Return the content of the Capture/Compare Register 1
    return TIM2->CCR1;
}

uint32 TIM2_MeasurePeriod(void) {
    uint32 capture1 = 0;
    uint32 capture2 = 0;
    uint32 period = 0;

    // Poll until the first rising edge is captured
    while (!TIM2_CaptureEvent_Detected());
    capture1 = TIM2_GetCaptureValue();
    TIM2_ClearCaptureFlag();

    // Poll until the second rising edge is captured
    while (!TIM2_CaptureEvent_Detected());
    capture2 = TIM2_GetCaptureValue();
    TIM2_ClearCaptureFlag();

    // Calculate the period, handling timer overflow
    if (capture2 > capture1) {
        period = capture2 - capture1;
    } else {
        // Overflow occurred
        period = (0xFFFF - capture1) + capture2 + 1;
    }
    return period;
}

uint32 TIM2_MeasureFrequency(void) {
    // Get the period in timer ticks (microseconds with a 1MHz clock)
    uint32 period_ticks = TIM2_MeasurePeriod();

    if (period_ticks == 0) {
        return 0; // Avoid division by zero
    }

    // Frequency (Hz) = Timer Clock Frequency / Period (in ticks)
    // Timer clock is 1 MHz (1,000,000 Hz)
    uint32 frequency = 1000000 / period_ticks;
    return frequency;
}