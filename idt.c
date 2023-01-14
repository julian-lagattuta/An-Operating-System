#include "idt.h"
#include "mainc.h"
//NOT MY CODE RIPPED STRAIGHT FROM A GUIDE
void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

typedef struct  idt_entry{
    unsigned short low_offset;
    unsigned short segment_selector;
    unsigned char zeros;
    unsigned char flags;
    unsigned short high_offset;
}idt_entry; 

typedef struct idt_p{
    unsigned short size;
    unsigned int pointer;
}__attribute__((packed)) idt_p;

idt_entry idt_entries[256];
idt_p idtp;
void set_idt(int index,unsigned int func_p ){
    idt_entry temp;
    temp.zeros = 0;

    temp.flags = 0x8E;

    temp.low_offset = func_p&0xffff;
    temp.high_offset = (func_p>>16)&0xffff;
    
    temp.segment_selector =0x08;
    idt_entries[index] = temp;
}
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* The interrupt routine's base address */
    idt_entries[num].low_offset = (base & 0xFFFF);
    idt_entries[num].high_offset = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt_entries[num].segment_selector = sel;
    idt_entries[num].zeros = 0;
    idt_entries[num].flags = flags;
}


extern void testfunc();
void install_idts(){
    set_idt(0, (unsigned int)error0);
    set_idt(1, (unsigned int)error1);
    set_idt(2, (unsigned int)error2);
    set_idt(3, (unsigned int)error3);
    set_idt(4, (unsigned int)error4);
    set_idt(5, (unsigned int)error5);
    set_idt(6, (unsigned int)error6);
    set_idt(7, (unsigned int)error7);
    set_idt(8, (unsigned int)error8);
    set_idt(9, (unsigned int)error9);
    set_idt(10, (unsigned int)error10);
    set_idt(11, (unsigned int)error11);
    set_idt(12, (unsigned int)error12);
    set_idt(13, (unsigned int)error13);
    set_idt(14, (unsigned int)error14);
    set_idt(15, (unsigned int)error15);
    set_idt(16, (unsigned int)error16);
    set_idt(17, (unsigned int)error17);
    set_idt(18, (unsigned int)error18);
    set_idt(19, (unsigned int)error19);
    set_idt(20, (unsigned int)error20);
    set_idt(21, (unsigned int)error21);
    set_idt(22, (unsigned int)error22);
    set_idt(23, (unsigned int)error23);
    set_idt(24, (unsigned int)error24);
    set_idt(25, (unsigned int)error25);
    set_idt(26, (unsigned int)error26);
    set_idt(27, (unsigned int)error27);
    set_idt(28, (unsigned int)error28);
    set_idt(29, (unsigned int)error29);
    set_idt(30, (unsigned int)error30);
    set_idt(31, (unsigned int)error31);

    set_idt(32,(unsigned int) int32);
    set_idt(33,(unsigned int) int33);
    set_idt(34,(unsigned int) int34);
    set_idt(35,(unsigned int) int35);
    set_idt(36,(unsigned int) int36);
    set_idt(37,(unsigned int) int37);
    set_idt(38,(unsigned int) int38);
    set_idt(39,(unsigned int) int39);
    set_idt(40,(unsigned int) int40);
    set_idt(41,(unsigned int) int41);
    set_idt(42,(unsigned int) int42);
    set_idt(43,(unsigned int) int43);
    set_idt(44,(unsigned int) int44);
    set_idt(45,(unsigned int) int45);
    set_idt(46,(unsigned int) int46);
    set_idt(47,(unsigned int) int47);
     


}




void extern flush_idts();


char* error_messages[] = {
    "Divide by zero (infinity)",
    "Debug ( this is actually  your fault)",
    "Non Maskable Interrupt (please wear a mask in public)",
    "Breakpoint (ok)",
    "Into Detected Overflow (stack overflow lmao ctrl+c ctrl v r/programmerhumor)",
    "Out of Bounds (which boundaries?????)",
    "Invalid Opcode (why did you write x86 by hand you dumb)",
    "No Coprocessor (DON'T TAKE THAT OUT!!!)",

    "Double Fault (2 faults)",
    "Coprocessor Segment Overrun (full overdrive?)",
    "Bad TSS (i don't like your tss, it sucks)" ,
    "Segment Not Present (que pasa)",
    "Stack Fault (manage your stack please)",
    "General Protection Fault (generalize your proection)",
    "Page Fault (it's your fault)",
    "Unknown Interrupt (well that's useless)",

    "Coprocessor Fault (what is a co processor)?",
    "Alignment Check (aligned?)",
    "Machine Check (bruh)",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
void error_handler( char value){
    
    if(value>sizeof(error_messages)-1){
        screenWrite("Unknown Error!!!");
    }else{
        screenWrite(error_messages[value]);
    }
}   
void(*interruptArr[0x20])();

void set_interrupt_func(int index, void(*func_p)()){
    interruptArr[index] = func_p;
}
void int_handler(char value){
    static count = 0;

    // screenWrite(b);
    if(interruptArr[value-32]){ 
        interruptArr[value-32]();
    }
    if (value >= 40)
    {
        outportb(0xA0, 0x20);
    }
    outportb(0x20, 0x20);
}

void do_idt(){
    memset(interruptArr,sizeof(interruptArr),0);
    irq_remap();

    memset(idt_entries,sizeof(idt_entries),0);
    idtp.pointer = idt_entries;
    idtp.size = sizeof(idt_entries)-1;

    flush_idts();
    install_idts();
    


}