
#define IOMUXC_CSI_VSYNC_GPIO4_IO19                 (volatile unsigned int *)(0x020E01DCU)   
#define CCM_CCGR3                                   (volatile unsigned int *)(0x020C4074U)

#define GPIO4                                       0X020A8000U
#define GPIO4_GDIR                                  (volatile unsigned int *)(GPIO4+0X04)
#define GPIO4_PSR                                   (volatile unsigned int *)(GPIO4+0X08)
#define GPIO4_ICR1                                  (volatile unsigned int *)(GPIO4+0X0c)
#define GPIO4_ICR2                                  (volatile unsigned int *)(GPIO4+0X10)
#define GPIO4_IMR                                   (volatile unsigned int *)(GPIO4+0X14)
#define GPIO4_ISR                                   (volatile unsigned int *)(GPIO4+0X18)
#define GPIO4_EDGE_SEL                              (volatile unsigned int *)(GPIO4+0X1c)

void gpio_init()
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