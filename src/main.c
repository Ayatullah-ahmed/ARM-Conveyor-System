#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"
#include "Exti.h"
#include "LCD.h"

#define __enable_irq()  (*((volatile uint32_t *)0xE000ED04) = 0)

#define EMERGENCY_BUTTON_PIN 2  /* PC2 */

volatile uint8 isEmergencyActive = 0;

void ShowEmergencyMessage(void) {
    LCD_Erase();
    LCD_Locate(0, 4);
    LCD_PrintText("EMERGENCY");
    LCD_Locate(1, 4);
    LCD_PrintText("STOP");
    Gpio_WritePin(GPIO_B, 9, !Gpio_ReadPin(GPIO_B, 9)); // Debug toggle
}

void ShowNormalMessage(void) {
    LCD_Erase();
    LCD_Locate(0, 0);
    LCD_PrintText("System Running");
    Gpio_WritePin(GPIO_B, 9, !Gpio_ReadPin(GPIO_B, 9)); // Debug toggle
}

void SetupClocks(void) {
    Rcc_Init();
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_GPIOC);
    Rcc_Enable(RCC_SYSCFG);
}

void SetupLCD(void) {
    LCD_Start();
    ShowNormalMessage();
}

void SetupButton(void) {
    Gpio_Init(GPIO_C, EMERGENCY_BUTTON_PIN, GPIO_INPUT, GPIO_PULL_UP);
    EXTI_Init();
}

int main(void) {
    SetupClocks();
    SetupLCD();
    SetupButton();

    while (1) {
        if (isEmergencyActive) {
            Gpio_WritePin(GPIO_B, 12, !Gpio_ReadPin(GPIO_B, 12)); // Debug toggle
            ShowEmergencyMessage();
            isEmergencyActive = 0; // Reset flag to allow toggling
        }
        for (volatile int i = 0; i < 100000; i++); // Short delay instead of Delay_Long
    }

    return 0;
}