#include "Exti.h"
#include "stm32f4xx.h"
#include "Gpio.h"

void EXTI_Init(void) {
    // Enable GPIOC clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Configure PC2 as input with pull-up
    Gpio_Init(GPIO_C, 2, GPIO_INPUT, GPIO_PULL_UP);

    // Enable SYSCFG clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Map PC2 to EXTI2 (EXTICR[0] bits 11:8 for EXTI2)
    SYSCFG->EXTICR[0] &= ~(0xF << 8); // Clear EXTI2 bits
    SYSCFG->EXTICR[0] |= (2 << 8);    // Set to Port C (2)

    // Configure EXTI2
    EXTI->IMR |= EXTI_IMR_MR2;        // Enable interrupt on EXTI2
    EXTI->FTSR |= EXTI_FTSR_TR2;      // Set falling edge trigger
    EXTI->PR |= EXTI_PR_PR2;          // Clear any pending interrupt

    // Configure NVIC for EXTI2
    NVIC_SetPriority(EXTI2_IRQn, 0);  // Set highest priority
    NVIC_EnableIRQ(EXTI2_IRQn);

}

void EXTI2_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR2) {     // Check if EXTI2 triggered
        EXTI->PR |= EXTI_PR_PR2;      // Clear pending bit
        isEmergencyActive = 1;        // Set flag for LCD update
        // Debug: Toggle PB8 to confirm interrupt
        Gpio_WritePin(GPIO_B, 8, !Gpio_ReadPin(GPIO_B, 8));
    }
}