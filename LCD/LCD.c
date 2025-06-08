//
// Created by Ayatullah Ahmed on 6/6/2025.
// LCD.c

#include "LCD.h"
#include <stdio.h>

// Delay Implementation with Nested Loops
void Delay_Short(uint32 microseconds) {
    for (uint32 outer = 0; outer < microseconds; outer++) {
        for (volatile uint32 inner = 0; inner < 5; inner++); // Approx 5 cycles per us at 4 MHz
    }
}

void Delay_Long(uint32 milliseconds) {
    for (uint32 outer = 0; outer < milliseconds; outer++) {
        for (volatile uint32 inner = 0; inner < 5000; inner++); // Approx 5000 cycles per ms at 4 MHz
    }
}

// Data Transmission Array Method
static const uint8 pinMap[4] = {LCD_D0_BIT, LCD_D1_BIT, LCD_D2_BIT, LCD_D3_BIT};
static void Send_DataChunk(uint8 value, enum LCD_Mode mode) {
    uint8 dataBits[4];
    dataBits[0] = (value >> 0) & 0x01;
    dataBits[1] = (value >> 1) & 0x01;
    dataBits[2] = (value >> 2) & 0x01;
    dataBits[3] = (value >> 3) & 0x01;

    Gpio_WritePin(LCD_CMD_PORT, LCD_RS_BIT, mode);
    for (uint8 i = 0; i < 4; i++) {
        Gpio_WritePin(LCD_DATA_PORT, pinMap[i], dataBits[i]);
    }
    Gpio_WritePin(LCD_CMD_PORT, LCD_E_BIT, HIGH_LEVEL);
    Delay_Short(2); // Extended pulse for reliability
    Gpio_WritePin(LCD_CMD_PORT, LCD_E_BIT, LOW_LEVEL);
    Delay_Short(150); // Extended delay for stability
}

// Command Execution
static void Execute_Command(enum LCD_Operation cmd) {
    Send_DataChunk(cmd >> 4, INSTRUCTION_MODE);
    Send_DataChunk(cmd & 0x0F, INSTRUCTION_MODE);
    Delay_Short(50); // Command execution delay
}

// Initialization Phases
static void Setup_Power(void) {
    Delay_Long(60); // Power stabilization
}

static void Configure_Pins(void) {
    Gpio_Init(LCD_CMD_PORT, LCD_RS_BIT, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_CMD_PORT, LCD_E_BIT, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D0_BIT, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D1_BIT, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D2_BIT, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D3_BIT, GPIO_OUTPUT, GPIO_PUSH_PULL);
}

static void Establish_Mode(void) {
    Send_DataChunk(0x03, INSTRUCTION_MODE); Delay_Long(6);
    Send_DataChunk(0x03, INSTRUCTION_MODE); Delay_Short(120);
    Send_DataChunk(0x03, INSTRUCTION_MODE); Delay_Short(120);
    Send_DataChunk(0x02, INSTRUCTION_MODE); Delay_Short(120);
}

static void Apply_Settings(void) {
    Execute_Command(LCD_SET_4BIT);
    Execute_Command(LCD_SHOW_ON);
    LCD_Erase();
}

void LCD_Start(void) {
    Setup_Power();
    Configure_Pins();
    Establish_Mode();
    Apply_Settings();
}

void LCD_Erase(void) {
    Execute_Command(LCD_CLEAR_ALL);
    Delay_Long(3); // Extended clear delay
}

void LCD_Locate(uint8 row, uint8 column) {
    uint8 addr;
    if (row == 0) addr = 0x80 + column;
    else if (row == 1) addr = 0xC0 + column;
    else if (row == 2) addr = 0x94 + column;
    else if (row == 3) addr = 0xD4 + column;
    else addr = 0x80 + column;
    Execute_Command((enum LCD_Operation)addr);
}

void LCD_Slide(uint8 direction) {
    Execute_Command(direction ? LCD_SHIFT_RIGHT : LCD_SHIFT_LEFT);
}

void LCD_ShiftPointer(uint8 direction) {
    Execute_Command(direction ? LCD_CURSOR_RIGHT : LCD_CURSOR_LEFT);
}

void LCD_PrintChar(uint8 character) {
    Send_DataChunk(character >> 4, CHARACTER_MODE);
    Send_DataChunk(character & 0x0F, CHARACTER_MODE);
    Delay_Short(50);
}

void LCD_PrintText(const char *text) {
    while (*text) {
        LCD_PrintChar(*text++);
    }
}

void LCD_PrintValue(uint16 value) {
    char temp[6];
    sprintf(temp, "%u", value);
    LCD_PrintText(temp);
}
