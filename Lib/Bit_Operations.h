#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

/* Bit manipulation macros */
#define SET_BIT(REG, BIT)       ((REG) |= (1U << (BIT)))
#define CLR_BIT(REG, BIT)       ((REG) &= ~(1U << (BIT)))
#define TOG_BIT(REG, BIT)       ((REG) ^= (1U << (BIT)))
#define GET_BIT(REG, BIT)       (((REG) >> (BIT)) & 1U)

#endif /* BIT_OPERATIONS_H */