[BITS 32]
global start
extern main
SECTION .text
start:
    ; mov al,0x13
    ; mov ah,0
    ; int 0x10
    mov ebp,_call_stack
    mov esp,_call_stack 

    call main
    jmp $
ALIGN 4
mboot:
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1

    MULTIBOOT_VGA_SETTINGS	equ 1<<2

    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE | MULTIBOOT_VGA_SETTINGS
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    

    dd mboot
    dd code
    dd bss
    dd end
    dd start
    dd 0
    dd 0
    dd 0
    dd 32
global gdt_flush
extern gdtp
gdt_flush:
    lgdt [gdtp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x8:long_jump_loc
long_jump_loc:
    ret

extern idtp
global flush_idts
flush_idts:
    lidt [idtp]
    ret
global error0
global error1
global error2
global error3
global error4
global error5
global error6
global error7
global error8
global error9
global error10
global error11
global error12
global error13
global error14
global error15
global error16
global error17
global error18
global error19
global error20
global error21
global error22
global error23
global error24
global error25
global error26
global error27
global error28
global error29
global error30
global error31

error0:

push byte 0
jmp error_routine

error1:
push byte 1
jmp error_routine

error2:
push byte 2
jmp error_routine

error3:
push byte 3
jmp error_routine

error4:
push byte 4
jmp error_routine

error5:
push byte 5
jmp error_routine

error6:
push byte 6
jmp error_routine

error7:
push byte 7
jmp error_routine

error8:
push byte 8
jmp error_routine

error9:
push byte 9
jmp error_routine

error10:
push byte 10
jmp error_routine

error11:
push byte 11
jmp error_routine

error12:
push byte 12
jmp error_routine

error13:
push byte 13
jmp error_routine

error14:
push byte 14
jmp error_routine

error15:
push byte 15
jmp error_routine

error16:
push byte 16
jmp error_routine

error17:
push byte 17
jmp error_routine

error18:
push byte 18
jmp error_routine

error19:
push byte 19
jmp error_routine

error20:
push byte 20
jmp error_routine

error21:
push byte 21
jmp error_routine

error22:
push byte 22
jmp error_routine

error23:
push byte 23
jmp error_routine

error24:
push byte 24
jmp error_routine

error25:
push byte 25
jmp error_routine

error26:
push byte 26
jmp error_routine

error27:
push byte 27
jmp error_routine

error28:
push byte 28
jmp error_routine

error29:
push byte 29
jmp error_routine

error30:
push byte 30
jmp error_routine

error31:
push byte 31
jmp error_routine


extern error_handler

error_routine:
pusha 
push ds
push es
push fs
push gs
mov ax,0x10
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax
mov ax,  [esp+48]
push ax
call error_handler
pop ax
pop gs 
pop fs
pop es
pop ds
popa
add esp,4   
iret



global int32
global int33
global int34
global int35
global int36
global int37
global int38
global int39
global int40
global int41
global int42
global int43
global int44
global int45
global int46
global int47

int32:
push byte 32
jmp int_routine

int33:
push byte 33
jmp int_routine

int34:
push byte 34
jmp int_routine

int35:
push byte 35
jmp int_routine

int36:
push byte 36
jmp int_routine

int37:
push byte 37
jmp int_routine

int38:
push byte 38
jmp int_routine

int39:
push byte 39
jmp int_routine

int40:
push byte 40
jmp int_routine

int41:
push byte 41
jmp int_routine

int42:
push byte 42
jmp int_routine

int43:
push byte 43
jmp int_routine

int44:
push byte 44
jmp int_routine

int45:
push byte 45
jmp int_routine

int46:
push byte 46
jmp int_routine

int47:
push byte 47
jmp int_routine
; eax: function id
; ebx: p1
; ecx: p2
; edx: p3
; esi: p4
; edi: p5


extern syscall_handler
global syscall_routine
syscall_routine:
push esp
push ebp

push ds
push es
push fs
push gs

push ax
mov ax,0x10
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax
pop ax


push edi
push esi
push edx
push ecx
push ebx
push eax
mov eax, [esp+32]
push eax
call syscall_handler
pop eax ;repeat on purpose to make up for push
pop eax
pop ebx
pop ecx
pop edx
pop esi
pop edi

pop gs 
pop fs
pop es
pop ds

pop ebp
pop esp
iret


extern int_handler
int_routine:
pusha 
push ds
push es
push fs
push gs
mov ax,0x10
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax
mov ax,  [esp+48]
push ax
call int_handler
pop ax
pop gs 
pop fs
pop es
pop ds
popa
add esp,4   
iret

extern screenWrite
global testfunc
testfunc:
    cli
    push hola
    call screenWrite
    add esp, 4
    iret


global enablePaging
enablePaging:
    mov eax, DWORD[esp]
    mov cr3, eax

    mov eax, cr0
    or eax, 2147483649
    mov cr0, eax
    nop
    ret
SECTION .data
hola:
db "hello"
SECTION .bss
    resb 8192 
_call_stack:
