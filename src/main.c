#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"
#include "Timer.h"
#include "Exti.h"
#include "LCD.h"
#include "ADC.h"
#include "PWM.h"
#include "ObjectDetection.h"

void Delay_Ms(volatile uint32 count) {
    while(count--);
}
#define __enable_irq()  (*((volatile uint32_t *)0xE000ED04) = 0)

#define EMERGENCY_BUTTON_PIN 2  /* PC2 */
#define IR_SENSOR_PIN 1         /* PC1 - IR sensor simulation (push button) */

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
    
    // Initialize Object Detection
    ObjectDetection_Init();

    // marcilino Variables
    uint16 pot_value;
    uint8 motor_percentage;
    char lcd_buffer[16]; // Buffer for LCD string formatting

    // Initialize LCD display
    LCD_Locate(0, 0);
    LCD_PrintText("Speed: 0%       ");
    LCD_Locate(1, 0);
    LCD_PrintText("Objects: 0   ");
    

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
        // Object detection processing
        ObjectDetection_Process();

        pot_value = ADC_ReadChannel(10);              // Read PC0 (Channel 10)
        motor_percentage = ADC_ValueToPercentage(pot_value); // Convert to 0–100%

        // Update PWM duty cycle
        PWM_SetDutyCycle(motor_percentage);            // Set motor speed

        // Update LCD with motor speed percentage (first row)
        LCD_Locate(0, 0);                              
        LCD_PrintText("Speed: ");                
        LCD_PrintValue(motor_percentage);              
        LCD_PrintText("%    ");                            // Clear leftover chars

        if (isEmergencyActive) {
            Gpio_WritePin(GPIO_B, 12, !Gpio_ReadPin(GPIO_B, 12)); // Debug toggle
            ShowEmergencyMessage();
            isEmergencyActive = 0; // Reset flag to allow toggling
        }
        
        // Short delay to allow proper polling frequency
        for (volatile int i = 0; i < 50000; i++); // Reduced delay for better edge detection
    }

    return 0;
}