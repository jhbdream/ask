
#include "common.h"
#include "uart.h"
#include "my_printf.h"
#include "gic.h"

void delay(volatile unsigned int d)
{
	while(d--);
}

int  main()
{	
	uart1_init();
	puts("hello world\r\n");

	gic_init();
	gic_enable_irq(GPIO4_Combined_16_31_IRQn);
	gpio_init();

	while(1);				
	return 0;
}


