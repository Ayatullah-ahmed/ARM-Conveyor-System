#ifndef UTILS_H
#define UTILS_H

#include "Std_Types.h"

/* Macro to access memory-mapped registers */
#define REG32(addr)             (*(volatile uint32*)(addr))
#define REG16(addr)             (*(volatile uint16*)(addr))
#define REG8(addr)              (*(volatile uint8*)(addr))

#endif /* UTILS_H */