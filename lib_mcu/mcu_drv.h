/*H**************************************************************************
* NAME:         mcu_drv.h         
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      cc03-canmon-0_0_1      
* REVISION:     1.7.8.2     
*----------------------------------------------------------------------------
* PURPOSE:
* This file contains the C51 driver definition
*****************************************************************************/

#ifndef _C51_DRV_H_
#define _C51_DRV_H_


/*_____ I N C L U D E S ____________________________________________________*/


/*_____ M A C R O S ________________________________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/
/* INTERRUPT NUMBER */
#define IRQ_INT0    0
#define IRQ_T0      1
#define IRQ_INT1    2
#define IRQ_T1      3
#define IRQ_UART    4
#define IRQ_PCA     5
#define IRQ_T2      6
#define IRQ_CAN     7
#define IRQ_ADC     8
#define IRQ_CAN_OVR 9
#define IRQ_SPI     10


/* SYSTEM MANAGEMENT */
#define MSK_SMOD1   0x80    /* PCON */
#define MSK_SMOD0   0x40
#define MSK_POF     0x10
#define MSK_GF1     0x08
#define MSK_GF0     0x04
#define MSK_PD      0x02
#define MSK_IDL     0x01

#define MSK_DPU     0x80    /* AUXR */
#define MSK_VPFDP   0x40
#define MSK_M0      0x20
#define MSK_XRS2    0x10
#define MSK_XRS1    0x08
#define MSK_XRS0    0x04
#define MSK_EXTRAM  0x02
#define MSK_AO      0x01


/* CLOCK */
#define MSK_X2      0x01    /* CKCON0 */
#define MSK_T0X2    0x02
#define MSK_T1X2    0x04
#define MSK_T2X2    0x08
#define MSK_UARTX2  0x10
#define MSK_PCAX2   0x20
#define MSK_WDX2    0x40
#define MSK_CANX2   0x80


#define MSK_SPIX2   0x01    /* CKCON1 */

/* TIMERS */
#define MSK_GATE1   0x80    /* TMOD */
#define MSK_C_T1    0x40
#define MSK_MO1     0x30
#define MSK_GATE0   0x08
#define MSK_C_T0    0x04
#define MSK_MO0     0x03


/* WATCHDOG */
#define MSK_WTO     0x07    /* WDTPRG*/

/* SPI */
#define MSK_SPSCR_SPIF		0x80
#define MSK_SPSCR_OVR		0x20
#define MSK_SPSCR_MODF		0x10
#define MSK_SPSCR_SPTE		0x08
#define MSK_SPSCR_UARTM		0x04
#define MSK_SPSCR_SPTEIE	0x02
#define MSK_SPSCR_MODFIE	0x01

#define MSK_SPCON_SPR2		0x80
#define MSK_SPCON_SPEN		0x40
#define MSK_SPCON_SSDIS		0x20
#define MSK_SPCON_MSTR		0x10
#define MSK_SPCON_CPOL		0x08
#define MSK_SPCON_CPHA		0x04
#define MSK_SPCON_SPR1		0x02
#define MSK_SPCON_SPR0		0x01

#define MSK_SPIF		0x80
#define MSK_OVR			0x20
#define MSK_MODF		0x10
#define MSK_SPTE		0x08
#define MSK_UARTM		0x04
#define MSK_SPTEIE		0x02
#define MSK_MODFIE		0x01

#define MSK_SPR2		0x80
#define MSK_SPEN		0x40
#define MSK_SSDIS		0x20
#define MSK_MSTR		0x10
#define MSK_CPOL		0x08
#define MSK_CPHA		0x04
#define MSK_SPR1		0x02
#define MSK_SPR0		0x01

/* ADC */
#define MSK_ADCON_PSIDLE 	0x40
#define MSK_ADCON_ADEN   	0x20
#define MSK_ADCON_ADEOC  	0x10
#define MSK_ADCON_ADSST  	0x08
#define MSK_ADCON_SCH    	0x07
#define MSK_ADDL_UTILS	 	0x03

#define MSK_PSIDLE 	0x40
#define MSK_ADEN   	0x20
#define MSK_ADEOC  	0x10
#define MSK_ADSST  	0x08
#define MSK_SCH    	0x07


/* FCON */
#define MSK_FCON_FBUSY 		0x01
#define MSK_FCON_FMOD  		0x06
#define MSK_FCON_FPS   		0x08
#define MSK_FCON_FPL   		0xF0
#define MSK_FSTA_FLOAD 		0x01
#define MSK_FSTA_SEQERR 	0x02

#define MSK_FBUSY 		0x01
#define MSK_FMOD  		0x06
#define MSK_FPS   		0x08
#define MSK_FPL   		0xF0
#define MSK_FLOAD 		0x01
#define MSK_SEQERR 		0x02


/* EECON */
#define MSK_EECON_EEBUSY 	0x01
#define MSK_EECON_EEE    	0x02
#define MSK_EECON_EEPL   	0xF0
#define MSK_AUXR_M0      	0x20
#define MSK_AUXR1_ENBOOT 	0x20

#define MSK_EEBUSY 	0x01
#define MSK_EEE    	0x02
#define MSK_EEPL   	0xF0
#define MSK_M0      0x20
#define MSK_ENBOOT 	0x20

/* CAN */
#define MSK_CANGIT_CANIT	0x80
#define MSK_CANGIT_OVRTIM   0x20
#define MSK_CANGIT_OVRBUF	0x10	
#define MSK_CANGIT_SERG		0x08
#define MSK_CANGIT_CERG		0x04
#define MSK_CANGIT_FERG		0x02
#define MSK_CANGIT_AERG		0x01
#define MSK_CANGSTA_OVFG	0x40
#define MSK_CANGSTA_TBSY	0x10
#define MSK_CANGSTA_RBSY	0x08
#define MSK_CANGSTA_ENFG	0x04
#define MSK_CANGSTA_BOFF	0x02
#define MSK_CANGSTA_ERRP	0x01
#define MSK_CANGCON_ABRQ   	0x80
#define MSK_CANGCON_OVRQ   	0x40
#define MSK_CANGCON_TTC   	0x20
#define MSK_CANGCON_SYNCTTC 0x10
#define TTC_EOF             0x10
#define TTC_SOF		        0x00
#define MSK_CANGCON_AUTBAUD 0x08
#define MSK_CANGCON_ENA  	0x02
#define MSK_CANGCON_GRES 	0x01
#define MSK_CANSTCH_DLCW  	0x80
#define MSK_CANSTCH_TxOk  	0x40
#define MSK_CANSTCH_RxOk  	0x20
#define MSK_CANSTCH_BERR  	0x10
#define MSK_CANSTCH_SERR  	0x08
#define MSK_CANSTCH_CERR  	0x04
#define MSK_CANSTCH_FERR  	0x02
#define MSK_CANSTCH_AERR  	0x01
#define MSK_CANCONCH_IDE  	0x10
#define MSK_CANCONCH_DLC  	0x0F
#define MSK_CANCONCH_CONF 	0xC0
#define DLC_MAX    8
#define CH_DISABLE 0x00
#define CH_RxENA   0x80
#define CH_TxENA   0x40
#define CH_RxBENA  0xC0
#define CAN_PRESCALER_MIN  0
#define CAN_PRESCALER_MAX  63
#define MSK_CANBT2_SJW  0x60
#define MSK_CANBT2_PRS  0x0E
#define CAN_SJW_MIN  0
#define CAN_SJW_MAX  3
#define CAN_PRS_MIN  0
#define CAN_PRS_MAX  7
#define MSK_CANBT3_PHS2 0x70
#define MSK_CANBT3_PHS1 0x0E
#define CAN_PHS2_MIN 0
#define CAN_PHS2_MAX 7
#define CAN_PHS1_MIN 0
#define CAN_PHS1_MAX 7
#define MSK_CANIDT4_RTRTAG 	0x04
#define MSK_CANGIE_ENRX    	0x20
#define MSK_CANGIE_ENTX    	0x10
#define MSK_CANGIE_ENERCH  	0x08
#define MSK_CANGIE_ENBUF   	0x04
#define MSK_CANGIE_ENERG   	0x02
#define MSK_CANIDM4_RTRMSK 	0x04
#define MSK_CANIDM4_IDEMSK 	0x01 

/* PCA */
#define MSK_CF				0x80 /*CCON*/
#define MSK_CR				0x40

#define MSK_CCF4			0x10
#define MSK_CCF3			0x08
#define MSK_CCF2			0x04
#define MSK_CCF1			0x02
#define MSK_CCF0			0x01

#define MSK_CDIL			0x80 
#define MSK_WDTE			0x40
#define MSK_CPS1			0x04
#define MSK_CPS0			0x02
#define MSK_ECF				0x01

#define MSK_ECM0			0x40 /*CCAPM0*/
#define MSK_CAPP0			0x20
#define MSK_CAPN0			0x10
#define MSK_MAT0			0x08
#define MSK_TOG0			0x04
#define MSK_PWM0			0x02
#define MSK_ECCF0			0x01

#define MSK_ECM1			0x40 /*CCAPM1*/
#define MSK_CAPP1			0x20
#define MSK_CAPN1			0x10
#define MSK_MAT1			0x08
#define MSK_TOG1			0x04
#define MSK_PWM1			0x02
#define MSK_ECCF1			0x01

#define MSK_ECM2			0x40 /*CCAPM2*/
#define MSK_CAPP2			0x20
#define MSK_CAPN2			0x10
#define MSK_MAT2			0x08
#define MSK_TOG2			0x04
#define MSK_PWM2			0x02
#define MSK_ECCF2			0x01

#define MSK_ECM3			0x40 /*CCAPM3*/
#define MSK_CAPP3			0x20
#define MSK_CAPN3			0x10
#define MSK_MAT3			0x08
#define MSK_TOG3			0x04
#define MSK_PWM3			0x02
#define MSK_ECCF3			0x01

#define MSK_ECM4			0x40 /*CCAPM4*/
#define MSK_CAPP4			0x20
#define MSK_CAPN4			0x10
#define MSK_MAT4			0x08
#define MSK_TOG4			0x04
#define MSK_PWM4			0x02
#define MSK_ECCF4			0x01

#define MSK_CCAP0H7			0x80 /*CCAP0H*/
#define MSK_CCAP0H6			0x40
#define MSK_CCAP0H5			0x20
#define MSK_CCAP0H4			0x10
#define MSK_CCAP0H3			0x08
#define MSK_CCAP0H2			0x04
#define MSK_CCAP0H1			0x02
#define MSK_CCAP0H0			0x01

#define MSK_CCAP1H7			0x80 /*CCAP1H*/
#define MSK_CCAP1H6			0x40
#define MSK_CCAP1H5			0x20
#define MSK_CCAP1H4			0x10
#define MSK_CCAP1H3			0x08
#define MSK_CCAP1H2			0x04
#define MSK_CCAP1H1			0x02
#define MSK_CCAP1H0			0x01

#define MSK_CCAP2H7			0x80 /*CCAP2H*/
#define MSK_CCAP2H6			0x40
#define MSK_CCAP2H5			0x20
#define MSK_CCAP2H4			0x10
#define MSK_CCAP2H3			0x08
#define MSK_CCAP2H2			0x04
#define MSK_CCAP2H1			0x02
#define MSK_CCAP2H0			0x01

#define MSK_CCAP3H7			0x80 /*CCAP3H*/
#define MSK_CCAP3H6			0x40
#define MSK_CCAP3H5			0x20
#define MSK_CCAP3H4			0x10
#define MSK_CCAP3H3			0x08
#define MSK_CCAP3H2			0x04
#define MSK_CCAP3H1			0x02
#define MSK_CCAP3H0			0x01

#define MSK_CCAP4H7			0x80 /*CCAP4H*/
#define MSK_CCAP4H6			0x40
#define MSK_CCAP4H5			0x20
#define MSK_CCAP4H4			0x10
#define MSK_CCAP4H3			0x08
#define MSK_CCAP4H2			0x04
#define MSK_CCAP4H1			0x02
#define MSK_CCAP4H0			0x01

#define MSK_CCAP0L7			0x80 /*CCAP0L*/
#define MSK_CCAP0L6			0x40
#define MSK_CCAP0L5			0x20
#define MSK_CCAP0L4			0x10
#define MSK_CCAP0L3			0x08
#define MSK_CCAP0L2			0x04
#define MSK_CCAP0L1			0x02
#define MSK_CCAP0L0			0x01

#define MSK_CCAP1L7			0x80 /*CCAP1L*/
#define MSK_CCAP1L6			0x40
#define MSK_CCAP1L5			0x20
#define MSK_CCAP1L4			0x10
#define MSK_CCAP1L3			0x08
#define MSK_CCAP1L2			0x04
#define MSK_CCAP1L1			0x02
#define MSK_CCAP1L0			0x01

#define MSK_CCAP2L7			0x80 /*CCAP2L*/
#define MSK_CCAP2L6			0x40
#define MSK_CCAP2L5			0x20
#define MSK_CCAP2L4			0x10
#define MSK_CCAP2L3			0x08
#define MSK_CCAP2L2			0x04
#define MSK_CCAP2L1			0x02
#define MSK_CCAP2L0			0x01

#define MSK_CCAP3L7			0x80 /*CCAP3L*/
#define MSK_CCAP3L6			0x40
#define MSK_CCAP3L5			0x20
#define MSK_CCAP3L4			0x10
#define MSK_CCAP3L3			0x08
#define MSK_CCAP3L2			0x04
#define MSK_CCAP3L1			0x02
#define MSK_CCAP3L0			0x01

#define MSK_CCAP4L7			0x80 /*CCAP4L*/
#define MSK_CCAP4L6			0x40
#define MSK_CCAP4L5			0x20
#define MSK_CCAP4L4			0x10
#define MSK_CCAP4L3			0x08
#define MSK_CCAP4L2			0x04
#define MSK_CCAP4L1			0x02
#define MSK_CCAP4L0			0x01




/*_____ D E C L A R A T I O N ______________________________________________*/

#define Set_x2_mode()           (CKCON0 |= MSK_X2)
#define Set_x1_mode()           (CKCON0 &= ~MSK_X2)
#define Mode_x2()               ((CKCON0 & MSK_X2) == MSK_X2)

#define Set_timer0_x1_mode()    (CKCON0 |= MSK_T0X2)
#define Set_timer0_x2_mode()    (CKCON0 &=~MSK_T0X2)
#define Set_timer1_x1_mode()    (CKCON0 |= MSK_T1X2)
#define Set_timer1_x2_mode()    (CKCON0 &=~MSK_T1X2)
#define Set_timer2_x1_mode()    (CKCON0 |= MSK_T2X2)
#define Set_timer2_x2_mode()    (CKCON0 &=~MSK_T2X2)
#define Set_uart_x1_mode()      (CKCON0 |= MSK_UARTX2)
#define Set_uart_x2_mode()      (CKCON0 &=~MSK_UARTX2)
#define Set_pca_x1_mode()()     (CKCON0 |= MSK_PCAX2)
#define Set_pca_x2_mode()       (CKCON0 &=~MSK_PCAX2)
#define Set_watchdog_x1_mode()	(CKCON0 |= MSK_WDX2)
#define Set_watchdog_x2_mode()	(CKCON0 &=~MSK_WDX2)
#define Set_can_x1_mode()		(CKCON0 |= MSK_CANX2)
#define Set_can_x2_mode()       (CKCON0 &=~MSK_CANX2)
#define Set_spi_x1_mode()		(CKCON1 |= MSK_SPIX2)
#define Set_spi_x2_mode()       (CKCON1 &=~MSK_SPIX2)


#define Set_idle_mode()         (PCON |= MSK_IDLE)
#define Set_power_down_mode()   (PCON |= MSK_PD)

#define Enable_xram()           (AUXR &= ~MSK_EXTRAM)
#define Disable_xram()          (AUXR |= MSK_EXTRAM)


#define Disable_ale()       	(AUXR |= MSK_AO)
#define Enable_ale()        	(AUXR &= ~MSK_AO)
#define Switch_ale()        	(AUXR ^= MSK_AO)

#define Enable_interrupt()     		 (EA = 1)
#define Disable_interrupt()     	 (EA = 0)
#define Enable_int0_interrupt()      (EX0 = 1)
#define Disable_int0interrupt()      (EX0 = 0)
#define Enable_timer0_interrupt()    (ET0 = 1)
#define Disable_timer0_interrupt()   (ET0 = 0)
#define Enable_int1_interrupt()      (EX1 = 1)
#define Disable_int1_interrupt()     (EX1 = 0)
#define Enable_timer1_interrupt()    (ET1 = 1)
#define Disable_timer1_interrupt()   (ET1 = 0)
#define Enable_pca_interrupt()       (EC = 1)
#define Disable_pca_interrupt()      (EC = 0)
#define Enable_uart_interrupt()      (ES = 1)
#define Disable_uart_interrupt()     (ES = 0)
#define Enable_timer2_interrupt()    (ET2 = 1)
#define Disable_timer2_interrupt()   (ET2 = 0)
#define Enable_can_interrupt()       (ECAN = 1)
#define Disable_can_interrupt()      (ECAN = 0)
#define Enable_adc_interrupt()       (EADC = 1)
#define Disable_adc_interrupt()      (EADC = 0)
#define Enable_can_ovr_interrupt()   (ETIM = 1)
#define Disable_can_ovr_interrupt()  (ETIM = 0)
#define Enable_spi_interrupt()   	 (ESPI = 1)
#define Disable_spi_interrupt()		 (ESPI = 0)

#define Uart_hw_init(config)    (SCON=(config))   
//#define Uart_set_baudrate(bdr) defined in /lib_mcu/uart/uart_bdr.h
#define Uart_enable()           (SCON|=MSK_UART_ENABLE_RX|MSK_UART_TX_READY)
#define Uart_tx_ready()         ((const bit)TI)
#define Uart_set_tx_busy()      (TI=0)
#define Uart_send_byte(ch)      (SBUF=ch)
#define Uart_rx_ready()         ((const bit)RI)
#define Uart_get_byte()         ((const char)SBUF)
#define Uart_ack_rx_byte()      (RI=0)

#endif  /* _C51_DRV_H_ */

