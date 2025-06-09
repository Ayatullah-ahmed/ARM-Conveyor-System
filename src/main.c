#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"
#include "Timer.h"
#include "LCD.h"

void Delay_Ms(volatile uint32 count) {
    while(count--);
}

int main(void) {
    // Initialize system
    Rcc_Init();
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_TIM2);

    // Initialize peripherals
    TIM2_InputCapture_Init();
    LCD_Start();
    LCD_Erase();

    LCD_Locate(0, 0);
    LCD_PrintText("Conveyor System");
    LCD_Locate(1, 0);
    LCD_PrintText("Speed: ");

    uint32 frequency = 0;

    while (1) {
        frequency = TIM2_MeasureFrequency();

        // Convert to RPM (example: 1 pulse per revolution)
        uint32 rpm = frequency * 60;

        LCD_Locate(1, 7);
        LCD_PrintValue(rpm);
        LCD_PrintText(" RPM");

        Delay_Ms(500);
    }
    return 0;
}