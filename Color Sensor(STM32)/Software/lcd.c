#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

#define ADDR 0x4E 

void lcd_cmd(char cmd) {
    char h, l;
    uint8_t d[4];
    h = (cmd & 0xf0);
    l = ((cmd << 4) & 0xf0);
    d[0] = h | 0x0C; 
    d[1] = h | 0x08; 
    d[2] = l | 0x0C; 
    d[3] = l | 0x08; 
    HAL_I2C_Master_Transmit(&hi2c1, ADDR, d, 4, 100);
}

void lcd_data(char data) {
    char h, l;
    uint8_t d[4];
    h = (data & 0xf0);
    l = ((data << 4) & 0xf0);
    d[0] = h | 0x0D; 
    d[1] = h | 0x09; 
    d[2] = l | 0x0D; 
    d[3] = l | 0x09; 
    HAL_I2C_Master_Transmit(&hi2c1, ADDR, d, 4, 100);
}

void lcd_clr(void) {
    lcd_cmd(0x80);
    for (int i=0; i<70; i++) lcd_data(' ');
}

void lcd_pos(int r, int c) {
    switch (r) {
        case 0: c |= 0x80; break;
        case 1: c |= 0xC0; break;
    }
    lcd_cmd(c);
}

void lcd_init(void) {
    HAL_Delay(50);
    lcd_cmd(0x30);
    HAL_Delay(5);
    lcd_cmd(0x30);
    HAL_Delay(1);
    lcd_cmd(0x30);
    HAL_Delay(10);
    lcd_cmd(0x20);
    HAL_Delay(10);
    lcd_cmd(0x28);
    HAL_Delay(1);
    lcd_cmd(0x08);
    HAL_Delay(1);
    lcd_cmd(0x01);
    HAL_Delay(2);
    lcd_cmd(0x06);
    HAL_Delay(1);
    lcd_cmd(0x0C);
}

void lcd_str(char *s) {
    while (*s) lcd_data(*s++);
}