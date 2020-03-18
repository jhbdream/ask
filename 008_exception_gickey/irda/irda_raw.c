
#include "irda_raw.h"

/* IRDA引脚 : EINT1/GPF1 */

static unsigned long long g_last_time = 0;

/* 
 * 配置GPIO, 注册中断
 * 在中断处理函数里:
      记录中断发生的时间,
      跟上次中断的时间比较, 计算出脉冲宽度
      读取引脚极性
      把数据放入环型缓冲区
 */

 /* 先实现GPIO的基本操作 */
static void irda_data_cfg_as_eint(void)
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
    *GPIO4_ICR2 |= (3<<6);
    *GPIO4_EDGE_SEL |= (1<19);
    
    /* 使能中断 */
    *GPIO4_IMR |= (1<<19);

}

static int irda_data_get(void)
{
	/*
	if ( (*GPIO4_DR) & (1<<19) )
		return 1;
	else
	*/
		printf ("[%d]", ( (*GPIO4_DR) >> 19 ) & 0x01);
		return ( (*GPIO4_DR) >> 19 ) & 0x01;

}

void irda_irq(int irq)
{
	/* 在中断处理函数里:
		 记录中断发生的时间,
		 跟上次中断的时间比较, 计算出脉冲宽度
		 读取引脚极性
		 把数据放入环型缓冲区
	*/
	irda_raw_event event;
	unsigned long long cur = get_system_time_us();
	
	event.duration = delta_time_us(g_last_time, cur);
	event.pol      = !irda_data_get();
	ir_event_put(&event);
	g_last_time = cur;
}


/* 注册中断 */
void irda_init(void)
{
	irda_data_cfg_as_eint();
}

void irda_raw_test(void)
{
	irda_raw_event event;
	unsigned long long pre = 0, cur;
	
	//irda_init();

	while (1)
	{
		if (0 == ir_event_get(&event))
		{
			cur = get_system_time_us();
			if (delta_time_us(pre, cur) > 1000000)
				printf("\n\r");
			pre = cur;
			printf("%s %d us | \n\r", event.pol? "hight" : "low", event.duration);
		}
	}
}

