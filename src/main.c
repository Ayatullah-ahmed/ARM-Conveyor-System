#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"
#include "Exti.h"
#include "LCD.h"
#include "Timer.h"
#include "ObjectDetection.h"

#define __enable_irq()  (*((volatile uint32 *)0xE000ED04) = 0)
#define EMERGENCY_BUTTON_PIN 2  /* PC2 */

volatile uint8 isEmergencyActive = 0;
static uint8 lastDisplayState = 0; // 0: normal, 1: emergency

void Delay_Ms(volatile uint32 count) {
    while(count--);
}

void ShowEmergencyMessage(void) {
    if (lastDisplayState != 1) {
        LCD_Erase();
        LCD_Locate(1, 6);
        LCD_PrintText("EMERGENCY");
        LCD_Locate(2, 8);
        LCD_PrintText("STOP");
        lastDisplayState = 1;
    }
    Gpio_WritePin(GPIO_B, 9, !Gpio_ReadPin(GPIO_B, 9)); // Debug toggle
}

void ShowNormalDisplay(void) {
    if (lastDisplayState != 0) {
        LCD_Erase();
        lastDisplayState = 0;
    }
    
    // Row 0: System Title
    LCD_Locate(0, 2);
    LCD_PrintText("Conveyor System");
    
    // Row 1: Speed Measurement from Timer
    LCD_Locate(1, 0);
    LCD_PrintText("Speed: ");
    uint32 frequency = TIM2_MeasureFrequency();
    LCD_PrintValue(frequency);
    LCD_PrintText(" Hz    ");
    
    // Row 2: Object Count from Both IR Sensors
    LCD_Locate(2, 0);
    LCD_PrintText("Objects: ");
    LCD_PrintValue(ObjectDetection_GetCount());
    LCD_PrintText("    ");
    
    // Row 3: Sensor Status (PC1=Button, PC7=Module)
    LCD_Locate(3, 0);
    LCD_PrintText("PC1:");
    LCD_PrintValue(!Gpio_ReadPin(GPIO_C, 1)); // Show 1 when active (inverted)
    LCD_PrintText(" PC7:");
    LCD_PrintValue(!Gpio_ReadPin(GPIO_C, 7)); // Show 1 when active (inverted)
    LCD_PrintText("     ");
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
    // Initialize LCD (20x4)
    LCD_Start();
    LCD_Erase();
    
    // Initialize Timer Input Capture for Speed Measurement (PA0)
    TIM2_InputCapture_Init();
    
    // Initialize Object Detection (PC1)
    ObjectDetection_Init();
    
    // Configure PC2 for EXTI2 (Emergency Button)
    Gpio_Init(GPIO_C, EMERGENCY_BUTTON_PIN, GPIO_INPUT, GPIO_PULL_UP);
    EXTI_Init(2, 2, 1); // Line 2, Port C (2), Falling edge (1)
    EXTI_Enable(2);
    
    // Show initialization message
    LCD_Locate(1, 2);
    LCD_PrintText("Initializing...");
    Delay_Ms(50000); // Reduced initialization delay
}

int main(void) {
    SetupClocks();
    SetupPeripherals();

    __enable_irq(); // Enable global interrupts

    while (1) {
        if (isEmergencyActive) {
            ShowEmergencyMessage();
            // Reset emergency flag after showing message
            Delay_Ms(100000); // Reduced emergency display time
            isEmergencyActive = 0;
        } else {
            // Process Object Detection (software polling - no interrupts)
            ObjectDetection_Process();
            
            // Update normal display with all system information
            ShowNormalDisplay();
        }

        Gpio_WritePin(GPIO_B, 12, !Gpio_ReadPin(GPIO_B, 12)); // Debug toggle
        Delay_Ms(50); // Very short delay for responsive object detection (50ms)
    }

    return 0;
}