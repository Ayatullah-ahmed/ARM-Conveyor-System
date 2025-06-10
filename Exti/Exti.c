
#include "Exti.h"
#include "Gpio.h"
#include "Rcc.h"

// Array to store callback functions for each EXTI line
static EXTI_Callback_t EXTI_Callbacks[16] = {0};

// Map EXTI line to NVIC IRQ number
static uint8 EXTI_GetIRQn(uint8 line) {
    if (line == 0) return EXTI0_IRQn;
    if (line == 1) return EXTI1_IRQn;
    if (line == 2) return EXTI2_IRQn;
    if (line == 3) return EXTI3_IRQn;
    if (line == 4) return EXTI4_IRQn;
    if (line >= 5 && line <= 9) return EXTI9_5_IRQn;
    if (line >= 10 && line <= 15) return EXTI15_10_IRQn;
    return 0; // Invalid line
}

void EXTI_Init(uint8 line, uint8 port, uint8 trigger, uint8 priority, EXTI_Callback_t callback) {
    // Validate line (0-15 for STM32F4 EXTI lines)
    if (line > 15) return;

    // Store callback
    EXTI_Callbacks[line] = callback;

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

    // Configure trigger
    if (trigger == EXTI_TRIGGER_RISING || trigger == EXTI_TRIGGER_BOTH) {
        EXTI->RTSR |= (1 << line); // Enable rising edge
    } else {
        EXTI->RTSR &= ~(1 << line); // Disable rising edge
    }
    if (trigger == EXTI_TRIGGER_FALLING || trigger == EXTI_TRIGGER_BOTH) {
        EXTI->FTSR |= (1 << line); // Enable falling edge
    } else {
        EXTI->FTSR &= ~(1 << line); // Disable falling edge
    }

    // Clear pending interrupt
    EXTI->PR |= (1 << line);

    // Configure NVIC
    uint8 irqn = EXTI_GetIRQn(line);
    if (irqn != 0) {
        NVIC_IPR[irqn] = (priority << 4); // Set priority (shifted for STM32F4)
    }
}

void EXTI_Enable(uint8 line) {
    if (line > 15) return;
    EXTI->IMR |= (1 << line); // Enable interrupt
    uint8 irqn = EXTI_GetIRQn(line);
    if (irqn != 0) {
        NVIC_ISER0 |= (1 << (irqn % 32)); // Enable interrupt in NVIC
    }
}

void EXTI_Disable(uint8 line) {
    if (line > 15) return;
    EXTI->IMR &= ~(1 << line); // Disable interrupt
    uint8 irqn = EXTI_GetIRQn(line);
    if (irqn != 0) {
        NVIC_ICER0 |= (1 << (irqn % 32)); // Disable interrupt in NVIC
    }
}

void EXTI_ClearPending(uint8 line) {
    if (line > 15) return;
    EXTI->PR |= (1 << line); // Clear pending interrupt
}

// Interrupt Handlers
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1 << 0)) {
        EXTI->PR |= (1 << 0);
        if (EXTI_Callbacks[0]) EXTI_Callbacks[0]();
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1 << 1)) {
        EXTI->PR |= (1 << 1);
        if (EXTI_Callbacks[1]) EXTI_Callbacks[1]();
    }
}

void EXTI2_IRQHandler(void) {
    if (EXTI->PR & (1 << 2)) {
        EXTI->PR |= (1 << 2);
        if (EXTI_Callbacks[2]) EXTI_Callbacks[2]();
    }
}

void EXTI3_IRQHandler(void) {
    if (EXTI->PR & (1 << 3)) {
        EXTI->PR |= (1 << 3);
        if (EXTI_Callbacks[3]) EXTI_Callbacks[3]();
    }
}

void EXTI4_IRQHandler(void) {
    if (EXTI->PR & (1 << 4)) {
        EXTI->PR |= (1 << 4);
        if (EXTI_Callbacks[4]) EXTI_Callbacks[4]();
    }
}

void EXTI9_5_IRQHandler(void) {
    for (uint8 line = 5; line <= 9; line++) {
        if (EXTI->PR & (1 << line)) {
            EXTI->PR |= (1 << line);
            if (EXTI_Callbacks[line]) EXTI_Callbacks[line]();
        }
    }
}

void EXTI15_10_IRQHandler(void) {
    for (uint8 line = 10; line <= 15; line++) {
        if (EXTI->PR & (1 << line)) {
            EXTI->PR |= (1 << line);
            if (EXTI_Callbacks[line]) EXTI_Callbacks[line]();
        }
    }
}
