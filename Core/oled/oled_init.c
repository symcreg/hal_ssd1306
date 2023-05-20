//
// Created by symct on 2023/5/19.
//

#include "oled_init.h"


void oledStart() {
    sdaSet();
    HAL_Delay(1);
    clkSet();
    HAL_Delay(1);
    sdaReset();//拉低电平
    HAL_Delay(1);
    clkReset();
    HAL_Delay(1);
}

void oledStop(){
    sdaReset();
    HAL_Delay(1);
    clkSet();
    HAL_Delay(1);
    sdaSet();//拉高电平
    HAL_Delay(1);
}
void oledWaitTick(){
    clkSet();
    HAL_Delay(1);
    clkReset();
    HAL_Delay(1);
}
void oledWrite(uint8_t data){
    for(uint8_t i=0;i<8;i++){
        clkReset();
        if(data&0x80){
            sdaSet();
        }else{
            sdaReset();
        }
        clkSet();
        data<<=1;
    }
}
void oledWriteData(uint8_t data){
    oledStart();
    oledWrite(0x78);
    oledWaitTick();
    oledWrite(0x40);//表示写数据
    oledWaitTick();
    oledWrite(data);//写数据
    oledWaitTick();
    oledStop();
}
void oledWriteCommand(uint8_t command){
    oledStart();
    oledWrite(0x78);
    oledWaitTick();
    oledWrite(0x40);//表示写指令
    oledWaitTick();
    oledWrite(command);//写指令
    oledWaitTick();
    oledStop();
}
void oledRefresh(){
    for(uint8_t i=0;i<8;i++){
        oledWriteCommand(0xb0+i);//设置行起始地址
        oledWriteCommand(0x00);//设置低列起始地址
        oledWriteCommand(0x10);//设置高列起始地址
        for(uint16_t n=0;n<128;n++){
            oledWriteData(oledGram[n][i]);
        }
    }
}
void oledDisplayOn(){
    oledWriteCommand(0x8d);//电荷泵使能
    oledWriteCommand(0x14);//开启电荷泵
    oledWriteCommand(0xaf);//点亮屏幕
}
void oledDisplayOff(){
    oledWriteCommand(0x8d);//电荷泵使能
    oledWriteCommand(0x10);//关闭电荷泵
    oledWriteCommand(0xae);//熄灭屏幕
}
