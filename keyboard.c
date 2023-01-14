#include "mainc.h"


unsigned char kbus_shift[128] =
{
  0,  27, '!', '@', '#', '$', '%', '^', '&', '*',
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t', /* Tab */
  'Q', 'W', 'E', 'R',
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
  0, /* Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
  '"', '~',   0, /* Left shift */
  '|', 'Z', 'X', 'C', 'V', 'B', 'N',
  'M', '<', '>', '?',   0, /* Right shift */
  '*',
  0,	/* Alt */
  ' ',	/* Space */
  0,	/* Caps lock */
  0,	/* 59 - F1 key ... > */
  0,   0,   0,   0,   0,   0,   0,   0,
  0,	/* < ... F10 */
  0,	/* 69 - Num lock*/
  0,	/* Scroll Lock */
  0,	/* Home key */
  0,	/* Up Arrow */
  0,	/* Page Up */
  '-',
  0,	/* Left Arrow */
  0,
  0,	/* Right Arrow */
  '+',
  0,	/* 79 - End key*/
  0,	/* Down Arrow */
  0,	/* Page Down */
  0,	/* Insert Key */
  0,	/* Delete Key */
  0,   0,   0,
  0,	/* F11 Key */
  0,	/* F12 Key */
  0,	/* All others undefined */
};
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

typedef struct KBQueue{
  int start;
  int size;
  unsigned char queue[256];
}KBQueue;
void initQueue(KBQueue* k){
  k->size=0;
  k->start=0;
}
void enqueue(KBQueue* k,unsigned char value){
  k->queue[(k->start+k->size)%256] = value;
  k->size+=1;
}
unsigned char dequeue(KBQueue* k){
  unsigned char value= k->queue[(k->start+k->size-1)%256];
  k->size-=1;
  k->start+=1;
  k->start%= 256;
  return value;
}
KBQueue queue;


void keyboard_handler(){
  static char capsLock = 0;
  static char shift =  0; 
  
  unsigned char scancode = inportb(0x60);
  if(scancode<128){
    switch (scancode)
    {
    case 58:
      capsLock^=1;
      break;
    case 80:
      moveCursor(0,1);
      break;
    case 77:
      moveCursor(1,0);
      break;
    case 75:
      moveCursor(-1,0);
      break;
    case 72:
      moveCursor(0,-1);
      break;
    default:
        if(capsLock){
          putc(kbus_shift[scancode]);
        }else{
          putc(kbdus[scancode]);
        }
      break;
    }

  }
}

void setup_keyboard (){
    set_interrupt_func(1,keyboard_handler);
    initQueue(&queue);

}