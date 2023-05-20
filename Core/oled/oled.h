//
// Created by symct on 2023/5/19.
//

#ifndef HAL_SSD1306_OLED_H
#define HAL_SSD1306_OLED_H

//#include "oled_init.h"

#include "stm32f1xx.h"

void oledColorTurn(uint8_t i);
void oledDisplayOn();
void oledDisplayOff();
void oledDrawPoint(uint8_t x,uint8_t y);
void oledClearPoint(uint8_t x,uint8_t y);
void oledDrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
void oledDrawRectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
void oledDrawCircle(uint8_t x,uint8_t,uint8_t r);
void oledDrawChar(uint8_t x,uint8_t y,uint8_t ch,uint8_t size1);
void oledDrawString(uint8_t x,uint8_t y,const uint8_t *str,uint8_t size1);
void oledDrawNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);

#endif //HAL_SSD1306_OLED_H
