#include "main.h"
#include "lcd.h"
#include <stdio.h>

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;

typedef struct {
    uint8_t r, g, b;
    char hex[8];
} clr_t;

clr_t c_data;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
uint32_t adc_rd(uint32_t ch);

void get_clr(void) {
    uint32_t v_r = adc_rd(ADC_R_CH);
    uint32_t v_g = adc_rd(ADC_G_CH);
    uint32_t v_b = adc_rd(ADC_B_CH);

    c_data.r = (uint8_t)(v_r * 255 / 4095);
    c_data.g = (uint8_t)(v_g * 255 / 4095);
    c_data.b = (uint8_t)(v_b * 255 / 4095);

    sprintf(c_data.hex, "#%02X%02X%02X", c_data.r, c_data.g, c_data.b);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_I2C1_Init();

    lcd_init();
    lcd_clr();
    lcd_pos(0, 0);
    lcd_str("SYS_ACTIVE");
    HAL_Delay(500);

    while (1) {
        get_clr();

        char *st = "NONE ";
        if(HAL_GPIO_ReadPin(FLAG_PORT, FLAG_R_PIN)) st = "RED  ";
        else if(HAL_GPIO_ReadPin(FLAG_PORT, FLAG_G_PIN)) st = "GREEN";
        else if(HAL_GPIO_ReadPin(FLAG_PORT, FLAG_B_PIN)) st = "BLUE ";

        char b1[16], b2[16];
        sprintf(b1, "DET: %s", st);
        sprintf(b2, "HEX: %s", c_data.hex);

        lcd_pos(0, 0);
        lcd_str(b1);
        lcd_pos(1, 0);
        lcd_str(b2);

        HAL_Delay(200);
    }
}

uint32_t adc_rd(uint32_t ch) {
    ADC_ChannelConfTypeDef cfg = {0};
    cfg.Channel = ch;
    cfg.Rank = 1;
    cfg.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &cfg);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 5);
    uint32_t v = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return v;
}

static void MX_ADC1_Init(void) {
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    HAL_ADC_Init(&hadc1);
}

static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    HAL_I2C_Init(&hi2c1);
}

static void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef g_init = {0};
    g_init.Pin = FLAG_R_PIN|FLAG_G_PIN|FLAG_B_PIN;
    g_init.Mode = GPIO_MODE_INPUT;
    g_init.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(FLAG_PORT, &g_init);
}

void SystemClock_Config(void) {
    
}

void Error_Handler(void) {
    while(1);
}