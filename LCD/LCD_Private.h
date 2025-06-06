//
// Created by Ayatullah Ahmed on 6/6/2025.
//
#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

/* Pin Definitions */
#define LCD_PORT_A GPIO_A
#define LCD_PORT_B GPIO_B
#define RS_PIN  5  /* PA5 */
#define RW_PIN  7  /* PA7 */
#define E_PIN   2  /* PA2 */
#define D4_PIN  0  /* PB0 */
#define D5_PIN  1  /* PB1 */
#define D6_PIN  2  /* PB2 */
#define D7_PIN  3  /* PB3 */

/* LCD Commands */
#define LCD_CLEAR         0x01
#define LCD_HOME          0x02
#define LCD_ENTRY_MODE    0x06
#define LCD_DISPLAY_ON    0x0C
#define LCD_4BIT_MODE     0x28
#define LCD_SET_CURSOR    0x80


#endif