#ifndef EXTI_H
#define EXTI_H

#include "Std_Types.h"

// EXTI Register Definitions
typedef struct {
    volatile uint32 IMR;      // Interrupt Mask Register
    volatile uint32 EMR;      // Event Mask Register
    volatile uint32 RTSR;     // Rising Trigger Selection Register
    volatile uint32 FTSR;     // Falling Trigger Selection Register
    volatile uint32 SWIER;    // Software Interrupt Event Register
    volatile uint32 PR;       // Pending Register
} EXTI_TypeDef;

#define EXTI_BASE         (0x40013C00UL)
#define EXTI              ((EXTI_TypeDef *)EXTI_BASE)

// SYSCFG Register for EXTI configuration
#define SYSCFG_EXTICR1    (*(volatile uint32 *)(0x40013808UL))
#define SYSCFG_EXTICR2    (*(volatile uint32 *)(0x4001380CUL))
#define SYSCFG_EXTICR3    (*(volatile uint32 *)(0x40013810UL))
#define SYSCFG_EXTICR4    (*(volatile uint32 *)(0x40013814UL))

// NVIC Registers
#define NVIC_ISER0        (*(volatile uint32 *)(0xE000E100UL))
#define NVIC_ICER0        (*(volatile uint32 *)(0xE000E180UL))
#define NVIC_IPR          ((volatile uint32 *)(0xE000E400UL))

// Function Prototypes
void EXTI_Init(uint8 line, uint8 port, uint8 trigger);
void EXTI_Enable(uint8 line);
void EXTI_Disable(uint8 line);
void EXTI_ClearPending(uint8 line);
void EXTI2_IRQHandler(void);

#endif // EXTI_H