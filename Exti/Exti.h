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

// NVIC Registers (ISER0–ISER7, ICER0–ICER7, IPR)
#define NVIC_ISER0        (*(volatile uint32 *)(0xE000E100UL))
#define NVIC_ISER1        (*(volatile uint32 *)(0xE000E104UL))
#define NVIC_ISER2        (*(volatile uint32 *)(0xE000E108UL))
#define NVIC_ISER3        (*(volatile uint32 *)(0xE000E10CUL))
#define NVIC_ISER4        (*(volatile uint32 *)(0xE000E110UL))
#define NVIC_ISER5        (*(volatile uint32 *)(0xE000E114UL))
#define NVIC_ISER6        (*(volatile uint32 *)(0xE000E118UL))
#define NVIC_ISER7        (*(volatile uint32 *)(0xE000E11CUL))
#define NVIC_ICER0        (*(volatile uint32 *)(0xE000E180UL))
#define NVIC_ICER1        (*(volatile uint32 *)(0xE000E184UL))
#define NVIC_ICER2        (*(volatile uint32 *)(0xE000E188UL))
#define NVIC_ICER3        (*(volatile uint32 *)(0xE000E18CUL))
#define NVIC_ICER4        (*(volatile uint32 *)(0xE000E190UL))
#define NVIC_ICER5        (*(volatile uint32 *)(0xE000E194UL))
#define NVIC_ICER6        (*(volatile uint32 *)(0xE000E198UL))
#define NVIC_ICER7        (*(volatile uint32 *)(0xE000E19CUL))
#define NVIC_IPR          ((volatile uint32 *)(0xE000E400UL))

// EXTI Line to NVIC IRQ Mapping
#define EXTI0_IRQn        6
#define EXTI1_IRQn        7
#define EXTI2_IRQn        8
#define EXTI3_IRQn        9
#define EXTI4_IRQn        10
#define EXTI9_5_IRQn      23
#define EXTI15_10_IRQn    40

// Trigger Types
#define EXTI_TRIGGER_RISING  0
#define EXTI_TRIGGER_FALLING 1
#define EXTI_TRIGGER_BOTH    2

// Callback Function Type
typedef void (*EXTI_Callback_t)(void);

// Function Prototypes
void EXTI_Init(uint8 line, uint8 port, uint8 trigger, uint8 priority, EXTI_Callback_t callback);
void EXTI_Enable(uint8 line);
void EXTI_Disable(uint8 line);
void EXTI_ClearPending(uint8 line);

// Interrupt Handlers
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif // EXTI_H
