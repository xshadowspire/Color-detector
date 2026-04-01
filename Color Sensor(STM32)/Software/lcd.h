#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx_hal.h"

void lcd_init(void);
void lcd_cmd(char cmd);
void lcd_data(char data);
void lcd_str(char *s);
void lcd_pos(int r, int c);
void lcd_clr(void);

#endif