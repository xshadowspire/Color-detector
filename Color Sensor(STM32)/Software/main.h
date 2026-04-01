#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
void Error_Handler(void);

/* Hardware Mapping - ADC Channels */
#define ADC_R_CH        ADC_CHANNEL_1
#define ADC_G_CH        ADC_CHANNEL_2
#define ADC_B_CH        ADC_CHANNEL_3 


#define FLAG_R_PIN      GPIO_PIN_1    
#define FLAG_G_PIN      GPIO_PIN_2   
#define FLAG_B_PIN      GPIO_PIN_3  
#define FLAG_PORT       GPIOC

#define I2C_SCL_PIN     GPIO_PIN_6 
#define I2C_SDA_PIN     GPIO_PIN_7   
#define I2C_PORT        GPIOB

#define V_REF           3.3f
#define ADC_RES         4095.0f

#ifdef __cplusplus
}
#endif

#endif