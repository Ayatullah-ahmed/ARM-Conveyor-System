#ifndef GPIO_H
#define GPIO_H

#include "Std_Types.h"

/* PORT NAME */
#define GPIO_A 'A'
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'
#define GPIO_E 'E'

/* Pin Mode */
#define GPIO_INPUT 0x00
#define GPIO_OUTPUT 0x01
#define GPIO_AF 0x02
#define GPIO_ANALOG 0x03

/* Default State */
#define GPIO_PUSH_PULL  0x0
#define GPIO_OPEN_DRAIN 0x1

#define GPIO_NO_PULL 0x00
#define GPIO_PULL_UP 0x01
#define GPIO_PULL_DOWN 0x02

/* Alternate Function selection */
#define GPIO_AF0 0
#define GPIO_AF1 1
#define GPIO_AF2 2
#define GPIO_AF3 3
#define GPIO_AF4 4
#define GPIO_AF5 5
#define GPIO_AF6 6
#define GPIO_AF7 7
#define GPIO_AF8 8
#define GPIO_AF9 9
#define GPIO_AF10 10
#define GPIO_AF11 11
#define GPIO_AF12 12
#define GPIO_AF13 13
#define GPIO_AF14 14
#define GPIO_AF15 15

/* Data */
#define LOW 0x0
#define HIGH 0x1

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState);
void Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data);
uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber);

#endif