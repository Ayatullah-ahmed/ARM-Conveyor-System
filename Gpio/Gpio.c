#include "Std_Types.h"
#include "Gpio.h"
#include "Gpio_Private.h"
#include "Utils.h"
#include "Bit_Operations.h"



void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState) {
    switch (PortName)
    {
        case GPIO_B:
            if(PinMode == GPIO_INPUT) {
                GPIOB_MODER &= ~(0x01 << (2 * PinNumber));
                GPIOB_MODER &= ~(0x01 << ((2 * PinNumber)+1));
                if(DefaultState == GPIO_PULL_UP){
                    GPIOA_PUPDR |= (0x01 << (2 * PinNumber));
                    GPIOA_PUPDR &= ~(0x01 << (( 2 * PinNumber)+1));
                }
                else if (DefaultState == GPIO_PULL_DOWN) {
                    GPIOA_PUPDR &= ~(0x01 << (2 * PinNumber));
                    GPIOA_PUPDR |= (0x01 << ((2 * PinNumber)+1));
                }
            }
            else if( PinMode == GPIO_OUTPUT) {
                GPIOB_MODER |= (0x01 << (2 * PinNumber));
                GPIOB_MODER &= ~(0x01 << ((2 * PinNumber)+1));
                if(DefaultState == GPIO_PUSH_PULL) {
                    GPIOB_OTYPER &= ~(0x01 << PinNumber);
                }
                else if(DefaultState == GPIO_OPEN_DRAIN ) {
                    GPIOB_OTYPER |= (0x01 << PinNumber);
                }
            }
        break;


        case GPIO_A:
            break;
    }
}
void Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data)
{
    switch (PortName) {
        case GPIO_B:
            if(Data == HIGH) {
                GPIOB_ODR |= (0x01 << PinNumber);
            }
            else if (Data == LOW){
                GPIOB_ODR &= ~(0x01 << PinNumber);

            }
        break;
    }
}
