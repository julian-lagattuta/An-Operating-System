#include "mainc.h"
#include "cursor.h"
#include "idt.h"
#include "clock.h"
#include "page.h"
#include "stdos.h"




void screenWrite(char* string){
    volatile char* video = 0xB8000;
    while(*string){
        *video++ = *string++;
        *video++ = 13;
        
    }   
}




extern void setup_gdt();
int main(){

     setup_gdt();    

    do_idt();
    setup_keyboard();
    initCursor();

    setup_syscalls();

    setup_clock();
//    __asm__ volatile ("sti");       
    

    //     typedef struct xy{
    //     int x;
    //     int y;
    // }xy;
    // xy save;
    // xy* p = &save;
    //     set_reg_const(eax,2);
    // set_reg_var(ebx,p,m);
    // make_syscall();
    setupPaging();

    moveCursor(5,5);
    while(1){


    // __asm__ volatile ("mov $0, %ax");   
    // __asm__ volatile ("div %ax");
    }
    return 0;
}
