#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"
#include "Exti.h"
#include "LCD.h"
#include "ADC.h"
#include "PWM.h"

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
    Gpio_Init(GPIO_C, 0, GPIO_ANALOG, GPIO_PUSH_PULL);  // PC0 → analog mode
    ADC_Init();     // Initialize ADC1 for channel 10
    PWM_Init(); // Initialize PWM on TIM1 (PA8)
    LCD_Start(); // Initialize 16x2 LCD

    // marcilino Variables

    uint16 pot_value;
    uint8 motor_percentage;
    char lcd_buffer[16]; // Buffer for LCD string formatting

    while (1) {
        pot_value = ADC_ReadChannel(10);              // Read PC0 (Channel 10)
        motor_percentage = ADC_ValueToPercentage(pot_value); // Convert to 0–100%

        // 3. Update PWM duty cycle
        PWM_SetDutyCycle(motor_percentage);            // Set motor speed

        // 4. Update LCD with motor speed percentage
        LCD_Locate(0, 0);                              // Set cursor to first row, first column
        LCD_PrintText("Motor Speed: ");                // Display static text
        LCD_PrintValue(motor_percentage);              // Display percentage value
        LCD_PrintText("%");                            // Append percentage sign

        // 5. Clear second row to avoid leftover characters
        LCD_Locate(1, 0);
        LCD_PrintText("                ");            // 16 spaces to clear second row

        Delay_Long(100); // 100 ms delay for LCD refresh


        if (isEmergencyActive) {
            Gpio_WritePin(GPIO_B, 12, !Gpio_ReadPin(GPIO_B, 12)); // Debug toggle
            ShowEmergencyMessage();
            isEmergencyActive = 0; // Reset flag to allow toggling
        }
        for (volatile int i = 0; i < 100000; i++); // Short delay instead of Delay_Long
    }

    return 0;
}