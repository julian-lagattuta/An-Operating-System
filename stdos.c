#include "stdos.h"
#include "mainc.h"
#define abs(x) ((x >> 30) | 1) * x

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}  


void memset(int* p,int size,  unsigned int value){
    for(int i = 0;i<size;i++){
        p[i]= value;
    }
}   
void writeChar(unsigned char c){
    volatile char* video = 0xB8000;
    *video=c;
}
int screenLoc = 0;
void putc(unsigned char c){
        volatile char* video = 0xB8000;
    video[screenLoc++]=c;
    video[screenLoc++] = 13;
}
char* itoa(int og, char* buffer){
    char* bcopy = buffer;
    int num = abs(og);
    int size =0;
    if(num==0){
        bcopy[0]='0';
        bcopy[1]='\0';
        return;
    }
    while(num!=0){
        int v = num%10;
        *buffer++ = '0'+v;
        num =num/10; 
        size++;
    }
    if(og<0){
        *buffer++ ='-';
        size++;
    }
    
    char swap;
    for(int i =0;i<size/2;i++){
        swap = bcopy[size-1-i];    
        bcopy[size-i-1] = bcopy[i];
        bcopy[i] = swap;
    }
    
    *buffer++='\0'; 
    return bcopy;
}
char* uitoa(unsigned int og, char* buffer){
    char* bcopy = buffer;
    int num = og;
    int size =0;
    if(num==0){
        bcopy[0]='0';
        bcopy[1]='\0';
        return;
    }
    while(num!=0){
        int v = num%10;
        *buffer++ = '0'+v;
        num =num/10; 
        size++;
    }
    
    char swap;
    for(int i =0;i<size/2;i++){
        swap = bcopy[size-1-i];    
        bcopy[size-i-1] = bcopy[i];
        bcopy[i] = swap;
    }
    
    *buffer++='\0'; 
    return bcopy;
}

void printint(unsigned int a){
        char b[20];
    uitoa(a,b);
    screenWrite(b);
}
void writeCharAt(unsigned char c,unsigned int x, unsigned int y){
    volatile char* video = 0xB8000;
    video[y*SCREEN_WIDTH+x]=c;
}