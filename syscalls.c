#include "mainc.h"
#include "stdos.h"
#include "cursor.h"
/*
return: eax

eax: function id
ebx: p1
ecx: p2
edx: p3
esi: p4
edi: p5


0: moveCursor
1: setCursorPos
2: geCursorXY as struct {unsigned int x,unsigned y}
3: putc ebx at position (ecx,edx)
*/      
typedef struct IntPair{
    int x;
    int y;
}IntPair;
void syscall_handler(volatile unsigned short data_seg,volatile unsigned int eax,volatile unsigned int ebx,volatile unsigned int ecx,volatile unsigned int edx,volatile unsigned int esi,volatile unsigned int edi){
    IntPair xy;
    // printint(data_seg);
    // return;
    switch(eax){
        case 0:
            //move cursor
            moveCursor(ebx,ecx);
            break;
        case 1:
            //set cursor pos
            setCursorPos(ebx,ecx);
            break;
        case 2:
            //get mouse pos
            //eax: cursorx
            // screenWrite("asdsad");eqwad`
            //ebx: cursory
            getCursorPosition(&xy.x,&xy.y);  
            set_reg_var(eax,xy.x,r);
            set_reg_var(ebx,xy.y,m);

            set_reg_var(ecx,ebx,m);
            set_data_seg_var(data_seg);
            
            asm("mov %eax, (%ecx)");

            asm("mov %ebx, 4(%ecx)");
            set_data_seg_const(16);

            break;
        case 3:
            writeCharAt((unsigned char)ebx,ecx,edx);
            //write character

    }

}  
void setup_syscalls(){
    set_idt(0x80,(unsigned int) syscall_routine);
}