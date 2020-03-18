#ifndef _IRDA_RAW_H
#define _IRDA_RAW_H

typedef struct irda_raw_event {
	int pol; /* ?? */
	int duration;  /* ????, us */
}irda_raw_event, *p_irda_raw_event;


#define IOMUXC_CSI_VSYNC_GPIO4_IO19                 (volatile unsigned int *)(0x020E01DCU)   
#define CCM_CCGR3                                   (volatile unsigned int *)(0x020C4074U)

#define GPIO4                                       0X020A8000U
#define GPIO4_DR                                  	(volatile unsigned int *)(GPIO4+0X00)
#define GPIO4_GDIR                                  (volatile unsigned int *)(GPIO4+0X04)
#define GPIO4_PSR                                   (volatile unsigned int *)(GPIO4+0X08)
#define GPIO4_ICR1                                  (volatile unsigned int *)(GPIO4+0X0c)
#define GPIO4_ICR2                                  (volatile unsigned int *)(GPIO4+0X10)
#define GPIO4_IMR                                   (volatile unsigned int *)(GPIO4+0X14)
#define GPIO4_ISR                                   (volatile unsigned int *)(GPIO4+0X18)
#define GPIO4_EDGE_SEL                              (volatile unsigned int *)(GPIO4+0X1c)


#endif /* _IRDA_RAW_H */
