
#include "common.h"
#include "uart.h"
#include "my_printf.h"
#include "gic.h"


int  main()
{	
	uart1_init();
	puts("hello world\r\n");
	
	gic_init();
	gic_enable_irq(GPIO4_Combined_16_31_IRQn);
	gic_enable_irq(GPT2_IRQn);

	gpt_init(GPT2);

	irda_raw_test();	
	return 0;
}


