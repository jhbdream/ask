
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
    ir_gpio_init();
}

static int irda_data_get(void)
{
	return get_ir_gpio_date();
}

/*irda�жϴ�����*/
void irda_irq(int irq)
{
	/* ���жϴ�������:
		 ��¼�жϷ�����ʱ��,
		 ���ϴ��жϵ�ʱ��Ƚ�, �����������
		 ��ȡ���ż���
		 �����ݷ��뻷�ͻ�����
	*/
	irda_raw_event event;
	/*��õ�ǰʱ�䲢��ֵ��cur*/
	unsigned long long cur = get_system_time_us();
	/*�ϴ�ʱ������ʱ��Ĳ�ֵ��Ҳ��������*/
	event.duration = delta_time_us(g_last_time, cur);
	/*��ȡ���ż���*/
	event.pol      = !irda_data_get();
	/*������Ҫ���λ������ĺ������뻷�λ����� */
	ir_event_put(&event);
	/*����ʱ��*/
	g_last_time = cur;
}

/* ��ʼ��ir��gpio */
void irda_init(void)
{
	irda_data_cfg_as_eint();
}

/*����ԭʼ����*/
void irda_raw_test(void)
{
	irda_raw_event event;
	unsigned long long pre = 0, cur;
	
	irda_init();

	while (1)
	{
		/*����ӻ��ѻ������������ݣ��Ͱ�����ӡ����*/
		if (0 == ir_event_get(&event))
		{
			cur = get_system_time_us();
			/*������ʱ����ϴ�ʱ�����Զ�Ļ����ʹ�ӡ�س�����*/
			if (delta_time_us(pre, cur) > 1000000)
				printf("\n\r");
			pre = cur;
			/*ʹ����Ŀ��������ж�pol�Ǹߵ�ƽ���ǵ͵�ƽ*/
			printf("%s %d us \n\r ", event.pol? "hight" : "low", event.duration);
		}
	}
}