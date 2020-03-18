#include "timer.h"


#define TIMER_NUM  32
static unsigned long long g_system_time_10ms_cnt = 0;


/* 寄存器地址参考数据手册1433页 
	定义GPT2寄存器地址
*/
#define GPT2_CR			(volatile unsigned int *)(0X020E8000)
#define GPT2_PR			(volatile unsigned int *)(0X020E8004)
#define GPT2_SR			(volatile unsigned int *)(0X020E8008)
#define GPT2_IR			(volatile unsigned int *)(0X020E800C)
#define GPT2_OCR1		(volatile unsigned int *)(0X020E8010)
#define GPT2_OCR2		(volatile unsigned int *)(0X020E8014)
#define GPT2_OCR3		(volatile unsigned int *)(0X020E8018)
#define GPT2_ICR1		(volatile unsigned int *)(0X020E801C)
#define GPT2_ICR2		(volatile unsigned int *)(0X020E8020)
#define GPT2_CNT		(volatile unsigned int *)(0X020E8024)


void gpt_init(GPT_Type *base)
{
	/* 进行软复位 */
	*GPT2_CR |= (1 << 15);
	/* 等待复位完成 */
	while((*GPT2_CR >> 15) & 0x1) {
	}

	/*
	 *
	 *bit9: 自动重新计数模式
	 *bit8-6: 时钟源选择 Peripheral Clock (ipg_clk)
	 *bit5: 使能停止模式
	 *bit3: 使能等待模式
	 *bit1: 失能时数据清零
	 */	
	*GPT2_CR = (1 << 6) | (1 << 5) | (1 << 3) | (1 << 1);

	/*
	 *设置时钟分频系数
	 */
	*GPT2_PR = 0;

	/*
	 *计数比较值，超过此数值重新计数
	 */
	*GPT2_OCR1 = 660000;

	/* 使能通道1中断 */
	*GPT2_IR = 1;

	/* 使能通用定时器 */
	*GPT2_CR |= 1;
}


void timer_irq(void)
{
	g_system_time_10ms_cnt++;
}

unsigned long long get_system_time_us(void)
{
	unsigned long long us = (*GPT2_CNT) / 66;
	return g_system_time_10ms_cnt * 10 * 1000 + us;
}

unsigned int delta_time_us(unsigned long long pre, unsigned long long now)
{
	return (now - pre);
}