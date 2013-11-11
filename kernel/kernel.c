#include "system.h"
#include "../drivers/display.h"
void help()
{
	print("Hi");
}

void clear()
{
	clear_screen();
}


void *memcpy(void *dest, const void *src, Size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, Size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, Size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

Size_t strlen(const char *str)
{
    Size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

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



int main()
{
    unsigned char c, d[10] ;
    c = 'a';
	char *video_memory = (char*)0xb8000 ;
	*video_memory = 'y';
	clear_screen();
	print("\n          MicroOS             \n");
	timer_install();
	keyboard_install();
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    print("\n-----------------------------------");
    print("\nmicroOS>> ");
	
	//putch();
	__asm__ __volatile__ ("sti");
    
    
        keyboard_handler();
        
        

    //puts("Hello World!\n");

    for (;;);

	return 0; 
}
