#include "Std_Types.h"
#include "Gpio.h"
#include "Gpio_Private.h"
#include "Utils.h"

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState) {
    switch (PortName) {
        case GPIO_A:
            if(PinMode == GPIO_INPUT) {
                GPIOA_MODER &= ~(0x03 << (2 * PinNumber));
                if(DefaultState == GPIO_PULL_UP){
                    GPIOA_PUPDR |= (0x01 << (2 * PinNumber));
                    GPIOA_PUPDR &= ~(0x01 << ((2 * PinNumber)+1));
                }
                else if (DefaultState == GPIO_PULL_DOWN) {
                    GPIOA_PUPDR &= ~(0x01 << (2 * PinNumber));
                    GPIOA_PUPDR |= (0x01 << ((2 * PinNumber)+1));
                }
            }
            else if(PinMode == GPIO_OUTPUT) {
                GPIOA_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOA_MODER |= (0x01 << (2 * PinNumber));
                if(DefaultState == GPIO_PUSH_PULL) {
                    GPIOA_OTYPER &= ~(0x01 << PinNumber);
                }
                else if(DefaultState == GPIO_OPEN_DRAIN) {
                    GPIOA_OTYPER |= (0x01 << PinNumber);
                }
            }
            else if(PinMode == GPIO_AF) {
                // Set MODER to Alternate Function mode (0b10)
                GPIOA_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOA_MODER |= (0x02 << (2 * PinNumber));

                // Configure Alternate Function
                if (PinNumber < 8) {
                    GPIOA_AFRL &= ~(0x0F << (4 * PinNumber));
                    GPIOA_AFRL |= (DefaultState << (4 * PinNumber));
                } else {
                    uint32 shift = (PinNumber - 8) * 4;
                    GPIOA_AFRH &= ~(0x0F << shift);
                    GPIOA_AFRH |= (DefaultState << shift);
                }

                // Disable pull-up/pull-down
                GPIOA_PUPDR &= ~(0x03 << (2 * PinNumber));
            }
            else if(PinMode == GPIO_ANALOG) {
                // Set MODER to Analog mode (0b11)
                GPIOA_MODER |= (0x03 << (2 * PinNumber));
            }
            break;

        case GPIO_B:
            if(PinMode == GPIO_INPUT) {
                GPIOB_MODER &= ~(0x03 << (2 * PinNumber));
                if(DefaultState == GPIO_PULL_UP){
                    GPIOB_PUPDR |= (0x01 << (2 * PinNumber));
                    GPIOB_PUPDR &= ~(0x01 << ((2 * PinNumber)+1));
                }
                else if (DefaultState == GPIO_PULL_DOWN) {
                    GPIOB_PUPDR &= ~(0x01 << (2 * PinNumber));
                    GPIOB_PUPDR |= (0x01 << ((2 * PinNumber)+1));
                }
            }
            else if(PinMode == GPIO_OUTPUT) {
                GPIOB_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOB_MODER |= (0x01 << (2 * PinNumber));
                if(DefaultState == GPIO_PUSH_PULL) {
                    GPIOB_OTYPER &= ~(0x01 << PinNumber);
                }
                else if(DefaultState == GPIO_OPEN_DRAIN) {
                    GPIOB_OTYPER |= (0x01 << PinNumber);
                }
            }
            else if(PinMode == GPIO_AF) {
                GPIOB_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOB_MODER |= (0x02 << (2 * PinNumber));

                if (PinNumber < 8) {
                    GPIOB_AFRL &= ~(0x0F << (4 * PinNumber));
                    GPIOB_AFRL |= (DefaultState << (4 * PinNumber));
                } else {
                    uint32 shift = (PinNumber - 8) * 4;
                    GPIOB_AFRH &= ~(0x0F << shift);
                    GPIOB_AFRH |= (DefaultState << shift);
                }
                GPIOB_PUPDR &= ~(0x03 << (2 * PinNumber));
            }
            else if(PinMode == GPIO_ANALOG) {
                GPIOB_MODER |= (0x03 << (2 * PinNumber));
            }
            break;

        case GPIO_C:
            if(PinMode == GPIO_INPUT) {
                GPIOC_MODER &= ~(0x03 << (2 * PinNumber));
                if(DefaultState == GPIO_PULL_UP){
                    GPIOC_PUPDR |= (0x01 << (2 * PinNumber));
                    GPIOC_PUPDR &= ~(0x01 << ((2 * PinNumber)+1));
                }
                else if (DefaultState == GPIO_PULL_DOWN) {
                    GPIOC_PUPDR &= ~(0x01 << (2 * PinNumber));
                    GPIOC_PUPDR |= (0x01 << ((2 * PinNumber)+1));
                }
            }
            else if(PinMode == GPIO_OUTPUT) {
                GPIOC_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOC_MODER |= (0x01 << (2 * PinNumber));
                if(DefaultState == GPIO_PUSH_PULL) {
                    GPIOC_OTYPER &= ~(0x01 << PinNumber);
                }
                else if(DefaultState == GPIO_OPEN_DRAIN) {
                    GPIOC_OTYPER |= (0x01 << PinNumber);
                }
            }
            else if(PinMode == GPIO_AF) {
                GPIOC_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOC_MODER |= (0x02 << (2 * PinNumber));

                if (PinNumber < 8) {
                    GPIOC_AFRL &= ~(0x0F << (4 * PinNumber));
                    GPIOC_AFRL |= (DefaultState << (4 * PinNumber));
                } else {
                    uint32 shift = (PinNumber - 8) * 4;
                    GPIOC_AFRH &= ~(0x0F << shift);
                    GPIOC_AFRH |= (DefaultState << shift);
                }
                GPIOC_PUPDR &= ~(0x03 << (2 * PinNumber));
            }
            else if(PinMode == GPIO_ANALOG) {
                GPIOC_MODER |= (0x03 << (2 * PinNumber));
            }
            break;

        case GPIO_D:
            if(PinMode == GPIO_INPUT) {
                GPIOD_MODER &= ~(0x03 << (2 * PinNumber));
                if(DefaultState == GPIO_PULL_UP){
                    GPIOD_PUPDR |= (0x01 << (2 * PinNumber));
                    GPIOD_PUPDR &= ~(0x01 << ((2 * PinNumber)+1));
                }
                else if (DefaultState == GPIO_PULL_DOWN) {
                    GPIOD_PUPDR &= ~(0x01 << (2 * PinNumber));
                    GPIOD_PUPDR |= (0x01 << ((2 * PinNumber)+1));
                }
            }
            else if(PinMode == GPIO_OUTPUT) {
                GPIOD_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOD_MODER |= (0x01 << (2 * PinNumber));
                if(DefaultState == GPIO_PUSH_PULL) {
                    GPIOD_OTYPER &= ~(0x01 << PinNumber);
                }
                else if(DefaultState == GPIO_OPEN_DRAIN) {
                    GPIOD_OTYPER |= (0x01 << PinNumber);
                }
            }
            else if(PinMode == GPIO_AF) {
                GPIOD_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOD_MODER |= (0x02 << (2 * PinNumber));

                if (PinNumber < 8) {
                    GPIOD_AFRL &= ~(0x0F << (4 * PinNumber));
                    GPIOD_AFRL |= (DefaultState << (4 * PinNumber));
                } else {
                    uint32 shift = (PinNumber - 8) * 4;
                    GPIOD_AFRH &= ~(0x0F << shift);
                    GPIOD_AFRH |= (DefaultState << shift);
                }
                GPIOD_PUPDR &= ~(0x03 << (2 * PinNumber));
            }
            else if(PinMode == GPIO_ANALOG) {
                GPIOD_MODER |= (0x03 << (2 * PinNumber));
            }
            break;

        case GPIO_E:
            if(PinMode == GPIO_INPUT) {
                GPIOE_MODER &= ~(0x03 << (2 * PinNumber));
                if(DefaultState == GPIO_PULL_UP){
                    GPIOE_PUPDR |= (0x01 << (2 * PinNumber));
                    GPIOE_PUPDR &= ~(0x01 << ((2 * PinNumber)+1));
                }
                else if (DefaultState == GPIO_PULL_DOWN) {
                    GPIOE_PUPDR &= ~(0x01 << (2 * PinNumber));
                    GPIOE_PUPDR |= (0x01 << ((2 * PinNumber)+1));
                }
            }
            else if(PinMode == GPIO_OUTPUT) {
                GPIOE_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOE_MODER |= (0x01 << (2 * PinNumber));
                if(DefaultState == GPIO_PUSH_PULL) {
                    GPIOE_OTYPER &= ~(0x01 << PinNumber);
                }
                else if(DefaultState == GPIO_OPEN_DRAIN) {
                    GPIOE_OTYPER |= (0x01 << PinNumber);
                }
            }
            else if(PinMode == GPIO_AF) {
                GPIOE_MODER &= ~(0x03 << (2 * PinNumber));
                GPIOE_MODER |= (0x02 << (2 * PinNumber));

                if (PinNumber < 8) {
                    GPIOE_AFRL &= ~(0x0F << (4 * PinNumber));
                    GPIOE_AFRL |= (DefaultState << (4 * PinNumber));
                } else {
                    uint32 shift = (PinNumber - 8) * 4;
                    GPIOE_AFRH &= ~(0x0F << shift);
                    GPIOE_AFRH |= (DefaultState << shift);
                }
                GPIOE_PUPDR &= ~(0x03 << (2 * PinNumber));
            }
            else if(PinMode == GPIO_ANALOG) {
                GPIOE_MODER |= (0x03 << (2 * PinNumber));
            }
            break;
    }
}

void Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data) {
    switch (PortName) {
        case GPIO_A:
            if(Data == HIGH) {
                GPIOA_ODR |= (0x01 << PinNumber);
            }
            else if (Data == LOW) {
                GPIOA_ODR &= ~(0x01 << PinNumber);
            }
            break;

        case GPIO_B:
            if(Data == HIGH) {
                GPIOB_ODR |= (0x01 << PinNumber);
            }
            else if (Data == LOW) {
                GPIOB_ODR &= ~(0x01 << PinNumber);
            }
            break;

        case GPIO_C:
            if(Data == HIGH) {
                GPIOC_ODR |= (0x01 << PinNumber);
            }
            else if (Data == LOW) {
                GPIOC_ODR &= ~(0x01 << PinNumber);
            }
            break;

        case GPIO_D:
            if(Data == HIGH) {
                GPIOD_ODR |= (0x01 << PinNumber);
            }
            else if (Data == LOW) {
                GPIOD_ODR &= ~(0x01 << PinNumber);
            }
            break;

        case GPIO_E:
            if(Data == HIGH) {
                GPIOE_ODR |= (0x01 << PinNumber);
            }
            else if (Data == LOW) {
                GPIOE_ODR &= ~(0x01 << PinNumber);
            }
            break;
    }
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber) {
    uint8 pinValue = LOW;

    switch (PortName) {
        case GPIO_A:
            pinValue = (GPIOA_IDR >> PinNumber) & 0x01;
            break;

        case GPIO_B:
            pinValue = (GPIOB_IDR >> PinNumber) & 0x01;
            break;

        case GPIO_C:
            pinValue = (GPIOC_IDR >> PinNumber) & 0x01;
            break;

        case GPIO_D:
            pinValue = (GPIOD_IDR >> PinNumber) & 0x01;
            break;

        case GPIO_E:
            pinValue = (GPIOE_IDR >> PinNumber) & 0x01;
            break;

        default:
            // Invalid port - could add error handling here
            break;
    }

    return pinValue;
}