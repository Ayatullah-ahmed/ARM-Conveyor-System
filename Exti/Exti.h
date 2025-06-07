#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include "stm32f4xx.h"
#include "Std_Types.h"

extern volatile uint8 isEmergencyActive;

void EXTI_Init(void);
void EXTI2_IRQHandler(void);

#endif // EXTI_H