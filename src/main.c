#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"
#include "Exti.h"
#include "LCD.h"

#define __enable_irq()  (*((volatile uint32 *)0xE000ED04) = 0)
#define EMERGENCY_BUTTON_PIN 2  /* PC2 */

volatile uint8 isEmergencyActive = 0;
static uint8 lastDisplayState = 0; // 0: normal, 1: emergency

void Delay_Ms(volatile uint32 count) {
    while(count--);
}

void ShowEmergencyMessage(void) {
    if (lastDisplayState != 1) { // Update only if not already in emergency state
        LCD_Locate(0, 0);
        LCD_PrintText("EMERGENCY STOP   "); // Pad with spaces to clear row
        lastDisplayState = 1;
    }
    Gpio_WritePin(GPIO_B, 9, !Gpio_ReadPin(GPIO_B, 9)); // Debug toggle
}

void ShowNormalMessage(void) {
    if (lastDisplayState != 0) { // Update only if switching from emergency
        LCD_Locate(0, 0);
        LCD_PrintText("Conveyor System "); // Pad with spaces to clear row
        lastDisplayState = 0;
    }
    Gpio_WritePin(GPIO_B, 9, !Gpio_ReadPin(GPIO_B, 9)); // Debug toggle
}



void SetupClocks(void) {
    Rcc_Init();
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_GPIOC);
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_SYSCFG);
    Rcc_Enable(RCC_TIM2);
}

void SetupPeripherals(void) {
    // Configure PC2 for EXTI2
    Gpio_Init(GPIO_C, EMERGENCY_BUTTON_PIN, GPIO_INPUT, GPIO_PULL_UP);
    EXTI_Init(2, 2, 2); // Line 2, Port C (2), Both edges (2)
    EXTI_Enable(2);
    LCD_Start();
    LCD_Erase();
    LCD_Locate(0, 0);
    LCD_PrintText("Conveyor System");

}

int main(void) {
    SetupClocks();
    SetupPeripherals();

    __enable_irq(); // Enable global interrupts

    while (1) {
        if (isEmergencyActive) {
            ShowEmergencyMessage();
        } else {
            ShowNormalMessage();
        }


        Gpio_WritePin(GPIO_B, 12, !Gpio_ReadPin(GPIO_B, 12)); // Debug toggle
        Delay_Ms(100000); // Stable delay for display updates
    }

    return 0;
}