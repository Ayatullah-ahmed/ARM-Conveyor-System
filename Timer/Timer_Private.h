//
// Created by alizayan684 on 2025-06-09.
//

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

// TIM register bit definitions
#define TIM_CR1_CEN          (1UL << 0)    // Counter enable
#define TIM_CCMR1_CC1S_0     (1UL << 0)    // CC1 channel is configured as input, IC1 is mapped on TI1
#define TIM_CCER_CC1E        (1UL << 0)    // Capture/Compare 1 output enable

// Define TIM2 register structure and bit definitions
#define TIM2_BASE_ADDR       0x40000000
#define TIM2                 ((TIM_TypeDef*)TIM2_BASE_ADDR)

// Timer register offsets
typedef struct {
    volatile uint32 CR1;      // Control register 1
    volatile uint32 CR2;      // Control register 2
    volatile uint32 SMCR;     // Slave mode control register
    volatile uint32 DIER;     // DMA/Interrupt enable register
    volatile uint32 SR;       // Status register
    volatile uint32 EGR;      // Event generation register
    volatile uint32 CCMR1;    // Capture/compare mode register 1
    volatile uint32 CCMR2;    // Capture/compare mode register 2
    volatile uint32 CCER;     // Capture/compare enable register
    volatile uint32 CNT;      // Counter
    volatile uint32 PSC;      // Prescaler
    volatile uint32 ARR;      // Auto-reload register
    volatile uint32 RCR;      // Repetition counter register
    volatile uint32 CCR1;     // Capture/compare register 1
    volatile uint32 CCR2;     // Capture/compare register 2
    volatile uint32 CCR3;     // Capture/compare register 3
    volatile uint32 CCR4;     // Capture/compare register 4
    volatile uint32 BDTR;     // Break and dead-time register
    volatile uint32 DCR;      // DMA control register
    volatile uint32 DMAR;     // DMA address for full transfer
} TIM_TypeDef;

#endif //TIMER_PRIVATE_H