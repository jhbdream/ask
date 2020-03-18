
#include "common.h"
#include "uart.h"
#include "my_printf.h"
#include "gic.h"

#define GPIO4                                       0X020A8000U
#define GPIO4_DR                                  	(volatile unsigned int *)(GPIO4+0X00)
void delay(volatile unsigned int d)
{
	while(d--);
}

int  main()
{	
	uart1_init();
	puts("hello world\r\n");
	
	irda_init();
	gpt_init(GPT2);

	gic_init();
	gic_enable_irq(GPIO4_Combined_16_31_IRQn);
	//gic_enable_irq(GPT2_IRQn);

	gpio_init();
	
	puts("all init\r\n");

	while(1) {
	//irda_raw_test();
			//printf ("[%d]\n", ( (*GPIO4_DR) >> 19 ) & 0x01);
			//delay(0XFFFFFFFFFF);
	}				
	return 0;
}


