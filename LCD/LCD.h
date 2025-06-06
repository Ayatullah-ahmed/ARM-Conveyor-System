//
// Created by Ayatullah Ahmed on 5/17/2025.
//

#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include "Std_Types.h"
#include "GPIO.h"

// Display Dimensions
#define LCD_ROW_COUNT    4
#define LCD_COL_COUNT    20
#define LCD_DATA_WIDTH   4

// Pin Definitions
#define LCD_CMD_PORT     GPIO_B
#define LCD_RS_BIT       0    // Register Select
#define LCD_E_BIT        1    // Enable
#define LCD_DATA_PORT    GPIO_B
#define LCD_D0_BIT       2    // Data Bit 0 (D4)
#define LCD_D1_BIT       3    // Data Bit 1 (D5)
#define LCD_D2_BIT       4    // Data Bit 2 (D6)
#define LCD_D3_BIT       5    // Data Bit 3 (D7)

// Pin States
#define HIGH_LEVEL       1
#define LOW_LEVEL        0

// Command Values
enum LCD_Operation {
    LCD_CLEAR_ALL     = 0x01,
    LCD_RETURN_START  = 0x02,
    LCD_MOVE_RIGHT    = 0x06,
    LCD_MOVE_LEFT     = 0x04,
    LCD_SHOW_ON       = 0x0C,
    LCD_SHOW_OFF      = 0x08,
    LCD_SHIFT_RIGHT   = 0x1C,
    LCD_SHIFT_LEFT    = 0x18,
    LCD_CURSOR_RIGHT  = 0x14,
    LCD_CURSOR_LEFT   = 0x10,
    LCD_SET_4BIT      = 0x28
};

// Mode Flags
enum LCD_Mode {
    INSTRUCTION_MODE = 0,
    CHARACTER_MODE   = 1
};

// Function Declarations
void LCD_Start(void);
void LCD_Erase(void);
void LCD_Locate(uint8 row, uint8 column);
void LCD_Slide(uint8 direction);
void LCD_ShiftPointer(uint8 direction);
void LCD_PrintChar(uint8 character);
void LCD_PrintText(const char *text);
void LCD_PrintValue(uint16 value);
void Delay_Short(uint32 microseconds);
void Delay_Long(uint32 milliseconds);

#endif // LCD_CONTROL_H