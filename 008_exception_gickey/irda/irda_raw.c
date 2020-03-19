
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
    ir_gpio_init();
}

static int irda_data_get(void)
{
	return get_ir_gpio_date();
}

/*irda中断处理函数*/
void irda_irq(int irq)
{
	/* 在中断处理函数里:
		 记录中断发生的时间,
		 跟上次中断的时间比较, 计算出脉冲宽度
		 读取引脚极性
		 把数据放入环型缓冲区
	*/
	irda_raw_event event;
	/*获得当前时间并赋值给cur*/
	unsigned long long cur = get_system_time_us();
	/*上次时间和这次时间的差值，也就是周期*/
	event.duration = delta_time_us(g_last_time, cur);
	/*获取引脚极性*/
	event.pol      = !irda_data_get();
	/*我们需要环形缓冲区的函数放入环形缓冲区 */
	ir_event_put(&event);
	/*更新时间*/
	g_last_time = cur;
}

/* 初始化ir的gpio */
void irda_init(void)
{
	irda_data_cfg_as_eint();
}

/*测试原始数据*/
void irda_raw_test(void)
{
	irda_raw_event event;
	unsigned long long pre = 0, cur;
	
	irda_init();

	while (1)
	{
		/*如果从唤醒缓冲区读到数据，就把它打印出来*/
		if (0 == ir_event_get(&event))
		{
			cur = get_system_time_us();
			/*如果这次时间和上次时间相差远的话，就打印回车换行*/
			if (delta_time_us(pre, cur) > 1000000)
				printf("\n\r");
			pre = cur;
			/*使用三目运算符来判断pol是高电平还是低电平*/
			printf("%s %d us \n\r ", event.pol? "hight" : "low", event.duration);
		}
	}
}