#include "Exti.h"
#include "Gpio.h"
#include "Rcc.h"

extern volatile uint8 isEmergencyActive;

void EXTI_Init(uint8 line, uint8 port, uint8 trigger) {
    // Validate line (0-15 for STM32F4 EXTI lines)
    if (line > 15) return;

    // Configure SYSCFG for EXTI line
    uint32 *exticr;
    uint8 shift;
    if (line < 4) {
        exticr = &SYSCFG_EXTICR1;
        shift = (line * 4);
    } else if (line < 8) {
        exticr = &SYSCFG_EXTICR2;
        shift = ((line - 4) * 4);
    } else if (line < 12) {
        exticr = &SYSCFG_EXTICR3;
        shift = ((line - 8) * 4);
    } else {
        exticr = &SYSCFG_EXTICR4;
        shift = ((line - 12) * 4);
    }
    *exticr &= ~(0xF << shift); // Clear EXTI line bits
    *exticr |= (port << shift); // Set port for EXTI line

    // Configure trigger (0: rising, 1: falling, 2: both)
    if (trigger == 0 || trigger == 2) {
        EXTI->RTSR |= (1 << line); // Enable rising edge
    } else {
        EXTI->RTSR &= ~(1 << line); // Disable rising edge
    }
    if (trigger == 1 || trigger == 2) {
        EXTI->FTSR |= (1 << line); // Enable falling edge
    } else {
        EXTI->FTSR &= ~(1 << line); // Disable falling edge
    }

    // Clear pending interrupt
    EXTI->PR |= (1 << line);

    // Configure NVIC (assuming line 2 uses IRQ8 for EXTI2)
    if (line == 2) {
        NVIC_IPR[8] = (0 << 0); // Set priority 0 (highest)
    }
}

void EXTI_Enable(uint8 line) {
    if (line > 15) return;
    EXTI->IMR |= (1 << line); // Enable interrupt
    if (line == 2) {
        NVIC_ISER0 |= (1 << 8); // Enable EXTI2 interrupt in NVIC (IRQ Separator)
    }
}

void EXTI_Disable(uint8 line) {
    if (line > 15) return;
    EXTI->IMR &= ~(1 << line); // Disable interrupt
    if (line == 2) {
        NVIC_ICER0 |= (1 << 8); // Disable EXTI2 interrupt in NVIC
    }
}

void EXTI_ClearPending(uint8 line) {
    if (line > 15) return;
    EXTI->PR |= (1 << line); // Clear pending interrupt
}

void EXTI2_IRQHandler(void) {
    if (EXTI->PR & (1 << 2)) { // Check if EXTI2 triggered
        EXTI->PR |= (1 << 2);  // Clear pending bit
        isEmergencyActive = 1;  // Set flag for emergency state
        Gpio_WritePin(GPIO_B, 8, !Gpio_ReadPin(GPIO_B, 8)); // Debug toggle
    }
}