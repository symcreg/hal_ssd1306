//
// Created by symct on 2023/5/19.
//

/*
 *  3v3     vcc
 *  GND     GND
 *  CLK     PC11
 *  SDA     PC12
 */

#ifndef HAL_SSD1306_OLED_INIT_H
#define HAL_SSD1306_OLED_INIT_H

#define clkReset() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET)
#define clkSet()  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET)

#define sdaReset() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET)
#define sdaSet()  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET)

#include "stm32f1xx.h"

extern uint8_t oledGram[128][8];

void oledStart();
void oledStop();
void oledWaitTick();
void oledWrite(uint8_t data);
void oledWriteData(uint8_t data);
void oledWriteCommand(uint8_t command);
void oledRefresh();
void oledDisplayOn();
void oledDisplayOff();


#endif //HAL_SSD1306_OLED_INIT_H
