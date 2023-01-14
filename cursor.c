#include "mainc.h"
#include "cursor.h"
volatile int cursorX =0;
volatile int cursorY=0;
void moveCursor(int relX,int relY){
    cursorX+=relX;
    cursorY+=relY;
    if(cursorX<0){
        if(cursorY>1){
            cursorY-=1;
            cursorX=79;
        }else{
            cursorX=0;
            cursorY=1;
        }
    }else if(cursorX>=80){
        cursorX=0;
        cursorY+=1;
    }else if(cursorY<1){
        cursorY=1;
        cursorX=0;
    }
    setCursorPos(cursorX,cursorY);
}  
void getCursorPosition  (int* x,int *y){
    *x=cursorX;
    *y=cursorY;
}
void setCursorPos(int x,int y){
    int pos = x+y*80;
    cursorX=x;
    cursorY=y;
    outportb(0x3d4,0xf);
    outportb(0x3d5,(unsigned char) (pos & 0xFF));
    outportb(0x3d4,0xe);
    outportb(0x3d5,(unsigned char) ((pos>>8)&0xff));
}
void initCursor(){
    outportb(0x3d4,0xa);
    outportb(0x3d5,(inportb(0x3d5)&0xc0)|0);
    outportb(0x3d4,0xb);
    outportb(0x3d5,(inportb(0x3d5)&0xe0)|1);
    cursorX=0;
    cursorY=0;  

}

