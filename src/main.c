// ───── Core Drivers ─────────────────────────────────────
#include "Std_Types.h"
#include "GPIO.h"
#include "Rcc.h"

// ───── Application Drivers ──────────────────────────────
#include "LCD.h"

void Init_LCD(void) {
    LCD_Start();
    LCD_Erase();
    LCD_Locate(0, 0);
    LCD_PrintText("LCD Test");
    LCD_Locate(1, 0);
    LCD_PrintText("Working?");
}

int main(void) {
    Rcc_Init();
    Rcc_Enable(RCC_GPIOB);
    Init_LCD();
    while (1) {
        Delay_Long(1000);
    }
    return 0;
}