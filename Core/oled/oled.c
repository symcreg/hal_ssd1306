//
// Created by symct on 2023/5/19.
//

#include "oled.h"
#include "oled_init.h"
#include "oled_font.h"

extern uint8_t oledGram[128][8];

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
void oledColorTurn(uint8_t i)
{
    if(i==0){
        oledWriteCommand(0xA6);//正常显示
    }
    if(i==1){
        oledWriteCommand(0xA7);//反显
    }
}
void oledDrawPoint(uint8_t x,uint8_t y){
    uint8_t i,m,n;
    i=y/8;
    m=y%8;
    n=1<<m;
    oledGram[x][i]|=n;
}
void oledClearPoint(uint8_t x,uint8_t y){
    uint8_t i,m,n;
    i=y/8;
    m=y%8;
    n=1<<m;
    oledGram[x][i]=~oledGram[x][i];
    oledGram[x][i]|=n;
    oledGram[x][i]=~oledGram[x][i];
}
void oledDrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2){
    uint16_t t;
    int xErr=0,yErr=0,deltaX,deltaY,distance;
    int incX,incY,uRow,uCol;
    deltaX= x2 - x1;
    deltaY= y2 - y1;
    uRow=x1;
    uCol=y1;
    if(deltaX > 0) {
        incX = 1;
    }
    else if (deltaX == 0) {
        incX = 0;
    }
    else {
        incX=-1;deltaX=-deltaX;
    }
    if(deltaY > 0) {
        incY = 1;
    }
    else if (deltaY == 0) {
        incY = 0;
    }
    else {
        incY=-1;deltaY=-deltaX;
    }
    if(deltaX > deltaY) {
        distance = deltaX;
    }
    else {
        distance = deltaY;
    }
    for(t=0;t<distance+1;t++){
        oledDrawPoint(uRow,uCol);
        xErr+=deltaX;
        yErr+=deltaY;
        if(xErr > distance){
            xErr-=distance;
            uRow+=incX;
        }
        if(yErr > distance){
            yErr-=distance;
            uCol+=incY;
        }
    }
}
void oledDrawRectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2){
    oledDrawLine(x1,y1,x1,y2);
    oledDrawLine(x1,y1,x2,y1);
    oledDrawLine(x1,y2,x2,y2);
    oledDrawLine(x2,y1,x2,y2);
}
void oledDrawCircle(uint8_t x,uint8_t y,uint8_t r){
    int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r){
        oledDrawPoint(x + a, y - b);
        oledDrawPoint(x - a, y - b);
        oledDrawPoint(x - a, y + b);
        oledDrawPoint(x + a, y + b);

        oledDrawPoint(x + b, y + a);
        oledDrawPoint(x + b, y - a);
        oledDrawPoint(x - b, y - a);
        oledDrawPoint(x - b, y + a);
        a++;
        num = (a * a + b * b) - r*r;
        if(num > 0){
            b--;
            a--;
        }
    }
}
void oledDrawChar(uint8_t x,uint8_t y,uint8_t ch,uint8_t size1){
    uint8_t i,m,temp,size2,ch1;
    uint8_t x0=x,y0=y;
    if(size1==8)size2=6;
    else size2=(size1/8+((size1%8)?1:0))*(size1/2);
    ch1= ch - ' ';
    for(i=0;i<size2;i++){
        if(size1==8){
            temp=asc2_0806[ch1][i];
        }
        else if(size1==12){
            temp=asc2_1206[ch1][i];
        }
        else if(size1==16){
            temp=asc2_1608[ch1][i];
        }
        else if(size1==24){
            temp=asc2_2412[ch1][i];
        }
        else return;
        for(m=0;m<8;m++)
        {
            if(temp&0x01) {
                oledDrawPoint(x, y);
            }
            else {
                oledClearPoint(x, y);
            }
            temp>>=1;
            y++;
        }
        x++;
        if((size1!=8)&&((x-x0)==size1/2)){
            x=x0;y0=y0+8;
        }
        y=y0;
    }
}
void oledDrawString(uint8_t x,uint8_t y,const uint8_t *str,uint8_t size1){
    while((*str>=' ')&&(*str<='~')){
        oledDrawChar(x,y,*str,size1);
        if(size1==8) {
            x += 6;
        }
        else {
            x += size1 / 2;
        }
        str++;
    }
}
uint32_t oledPow(uint8_t m,uint8_t n){
    uint32_t result=1;
    while(n--){
        result*=m;
    }
    return result;
}
void oledDrawNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1){
    uint8_t t,temp,m=0;
    if(size1==8) {
        m = 2;
    }
    for(t=0;t<len;t++){
        temp=(num/oledPow(10,len-t-1))%10;
        if(temp==0){
            oledDrawChar(x+(size1/2+m)*t,y,'0',size1);
        }
        else{
            oledDrawChar(x+(size1/2+m)*t,y,temp+'0',size1);
        }
    }
}