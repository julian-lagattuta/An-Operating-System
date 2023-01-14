char* uitoa(unsigned int og, char* buffer);
void writeChar(unsigned char c);
void putc(unsigned char c);
void printint(unsigned int a);
void screenWrite(char* string);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

void memset(int* p,int size,  unsigned int value);

void writeCharAt(unsigned char c,unsigned int x, unsigned int y);

typedef unsigned int uint32_t;

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define set_reg_const(reg,value)    __asm__ volatile ("mov $" #value ", %%" #reg: : :  #reg)
#define set_reg_var(reg,var,constraint) __asm__ volatile("mov %0, %%"#reg: : #constraint (var):#reg);
#define set_reg_reg(src,dest) __asm__ volatile ("mov %%"#src",%%"#dest: : : #src, #dest)
#define new_load_reg(reg) int reg;  __asm__ volatile ("mov %%"#reg ",%0" : "+m"(reg))
#define interrupt(a)    __asm__ volatile ("int $" #a)
#define make_syscall() __asm__ volatile ("int $0x80")
#define set_data_seg_const(value) __asm__ volatile ("push %ax; mov $"#value", %ax; mov %ax, %ds;pop %ax")
#define set_data_seg_var(var) __asm__ volatile ("mov %0, %%ds"::"m"(var))
#define asm __asm__ volatile
