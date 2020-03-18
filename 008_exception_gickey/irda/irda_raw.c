
#include "irda_raw.h"

/* IRDA���� : EINT1/GPF1 */

static unsigned long long g_last_time = 0;

/* 
 * ����GPIO, ע���ж�
 * ���жϴ�������:
      ��¼�жϷ�����ʱ��,
      ���ϴ��жϵ�ʱ��Ƚ�, �����������
      ��ȡ���ż���
      �����ݷ��뻷�ͻ�����
 */

 /* ��ʵ��GPIO�Ļ������� */
static void irda_data_cfg_as_eint(void)
{
   	unsigned int val=0;
    /* ʹ��GPIO4 ʱ�� */
    *CCM_CCGR3 |= (3<<12);

    /* �������Ÿ��ù���ΪGPIO */
    *IOMUXC_CSI_VSYNC_GPIO4_IO19 = 0x15;

    /* ����GPIOΪ����ģʽ */
    val = *GPIO4_GDIR;
	val &= ~(1<<19);
	*GPIO4_GDIR = val;
    
    /* ����Ϊ˫�����ж�ģʽ*/
    *GPIO4_ICR2 |= (3<<6);
    *GPIO4_EDGE_SEL |= (1<19);
    
    /* ʹ���ж� */
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
	/* ���жϴ�������:
		 ��¼�жϷ�����ʱ��,
		 ���ϴ��жϵ�ʱ��Ƚ�, �����������
		 ��ȡ���ż���
		 �����ݷ��뻷�ͻ�����
	*/
	irda_raw_event event;
	unsigned long long cur = get_system_time_us();
	
	event.duration = delta_time_us(g_last_time, cur);
	event.pol      = !irda_data_get();
	ir_event_put(&event);
	g_last_time = cur;
}


/* ע���ж� */
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

