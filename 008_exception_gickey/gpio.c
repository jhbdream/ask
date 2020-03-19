#include"gpio.h"

void ir_gpio_init()
{
    unsigned int val=0;
    /* 使能GPIO4 时钟 */
    *CCM_CCGR3 |= (3<<12);

    /* 设置引脚复用功能为GPIO */
    *IOMUXC_CSI_VSYNC_GPIO4_IO19 = 0x15;

    /* 设置GPIO为输入模式 */
    val = *GPIO4_GDIR;
	val &= ~(1<<19);
	*GPIO4_GDIR = val;
    
    /* 设置为双边沿中断模式*/
    *GPIO4_ICR2 |= (2<<6);
    *GPIO4_EDGE_SEL |= (1<<19);
    
    /* 使能中断 */
    *GPIO4_IMR |= (1<<19);
}

int get_ir_gpio_date()
{
	if ( (*GPIO4_PSR) & (1<<19) )
		return 1;
	else
		return 0;
}