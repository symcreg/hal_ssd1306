//
// Created by symct on 2023/5/19.
//

//128*48

#include "oled_init.h"

uint8_t oledGram[128][8];



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
    sdaSet();
    HAL_Delay(1);
    clkSet();
    HAL_Delay(1);
    clkReset();
    HAL_Delay(1);
}
void oledWrite(uint8_t data){
    for(uint8_t i=0;i<8;i++){

        if(data&0x80){
            sdaSet();
        }else{
            sdaReset();
        }
        clkSet();
        clkReset();
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
    oledWrite(0x00);//表示写指令
    oledWaitTick();
    oledWrite(command);//写指令
    oledWaitTick();
    oledStop();
}
void oledClear(){
    for(uint8_t i=0;i<8;i++){
        for(uint8_t n=0;n<128;n++){
            oledGram[n][i]=0;//清除数据
        }
    }
    oledRefresh();//更新显示
}




//slow?
void oledRefresh(){
    uint8_t i,n;
    for(i=0;i<8;i++){
        oledWriteCommand(0xb0+i);
        oledWriteCommand(0x00);
        oledWriteCommand(0x10);
        oledStart();
        oledWrite(0x78);
        oledWaitTick();
        oledWrite(0x40);
        oledWaitTick();
        for(n=0;n<128;n++){
            oledWrite(oledGram[n][i]);
            oledWaitTick();
        }
        oledStop();
    }
}

void oledInit(){
    oledWriteCommand(0xAE);//--turn off oled panel
    oledWriteCommand(0x00);//---set low column address
    oledWriteCommand(0x10);//---set high column address
    oledWriteCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    oledWriteCommand(0x81);//--set contrast control register
    oledWriteCommand(0xCF);// Set SEG Output Current Brightness
    oledWriteCommand(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    oledWriteCommand(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    oledWriteCommand(0xA6);//--set normal display
    oledWriteCommand(0xA8);//--set multiplex ratio(1 to 64)
    oledWriteCommand(0x3f);//--1/64 duty
    oledWriteCommand(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    oledWriteCommand(0x00);//-not offset
    oledWriteCommand(0xd5);//--set display clock divide ratio/oscillator frequency
    oledWriteCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    oledWriteCommand(0xD9);//--set pre-charge period
    oledWriteCommand(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    oledWriteCommand(0xDA);//--set com pins hardware configuration
    oledWriteCommand(0x12);
    oledWriteCommand(0xDB);//--set vcomh
    oledWriteCommand(0x40);//Set VCOM Deselect Level
    oledWriteCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    oledWriteCommand(0x02);//
    oledWriteCommand(0x8D);//--set Charge Pump enable/disable
    oledWriteCommand(0x14);//--set(0x10) disable
    oledWriteCommand(0xA4);// Disable Entire Display On (0xa4/0xa5)
    oledWriteCommand(0xA6);// Disable Inverse Display On (0xa6/a7)
//    oledClear();
    oledWriteCommand(0xAF);
    oledWriteCommand(0xC8);//屏幕方向正常显示
    oledWriteCommand(0xA1);
}