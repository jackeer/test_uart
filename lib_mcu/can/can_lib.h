/*H***************************************************************************
* FILE_NAME:    can_lib.
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : J.S. BERTHY                                           
* FILE_CREATION_DATE: 28/09/99                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE: This file contains all prototypes and macros exported.      
******************************************************************************/

#ifndef _CAN_LIB_H_
#define _CAN_LIB_H_

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ C O N S T A N T E S - D E F I N I T I O N  ___________________________*/
#define NB_CHANNEL   15
#define NB_DATA_MAX   8

/*---- Index for table can_ident_t */
#define STD_ID_10_4 	0
#define STD_ID_3_0   	1
#define EXT_ID_28_21 	0
#define EXT_ID_20_13 	1
#define EXT_ID_12_5  	2
#define EXT_ID_4_0   	3

#define MSK_CTRL_RTR   0x80
#define MSK_CTRL_IDE   0x10
#define MSK_CTRL_DLC   0x0F


/* constant for configuration of conf_rx and conf_tx */

#define CONF_IDE       0x10
#define CONF_NOIDE     0
#define CONF_RTR       0x20
#define CONF_NORTR     0
#define CONF_BUFFER    0x01
#define CONF_NOBUFFER  0
#define CONF_MSK_IDE   0x80
#define CONF_NOMSK_IDE 0
#define CONF_MSK_RTR   0x4
#define CONF_NOMSK_RTR 0


/*_____ M A C R O S - DE C L A R A T I O N ___________________________________*/

#define CAN_CONTROLLER_ENABLE    { CANGCON |= MSK_CANGCON_ENA;  }
#define CAN_CONTROLLER_DISABLE   { CANGCON &= ~MSK_CANGCON_ENA; }
#define CAN_CONTROLLER_RESET     { CANGCON |= MSK_CANGCON_GRES; }

#define CAN_IT_ENABLE 			{ ECAN = 1; }
#define CAN_IT_DISABLE         	{ ECAN = 0; }
#define CANTIM_IT_ENABLE 		{ ETIM = 1; }
#define CANTIM_IT_DISABLE       { ETIM = 0; }

#define CAN_RX_IT_ENABLE         { CANGIE |= MSK_CANGIE_ENRX;  }
#define CAN_RX_IT_DISABLE        { CANGIE &= ~MSK_CANGIE_ENRX; }
#define CAN_TX_IT_ENABLE         { CANGIE |= MSK_CANGIE_ENTX;  }
#define CAN_TX_IT_DISABLE        { CANGIE &= ~MSK_CANGIE_ENTX; }
#define CAN_ERCH_IT_ENABLE       { CANGIE |= MSK_CANGIE_ENERCH;  }
#define CAN_ERCH_IT_DISABLE      { CANGIE &= ~MSK_CANGIE_ENERCH; }
#define CAN_ERG_IT_ENABLE        { CANGIE |= MSK_CANGIE_ENERG;  }
#define CAN_ERG_IT_DISABLE       { CANGIE &= ~MSK_CANGIE_ENERG; }
#define CAN_BUF_IT_ENABLE        { CANGIE |= MSK_CANGIE_ENBUF; }
#define CAN_BUF_IT_DISABLE       { CANGIE &= ~MSK_CANGIE_ENBUF;}

#define CAN_CHANNEL_IT_ENABLE(channel) {(channel < CHANNEL_8)?(CANIE2|=(1<<channel)):(CANIE1|=(1<<(channel-8)));}
#define CAN_CHANNEL_IT_DISABLE(channel) {(channel < CHANNEL_8)?(CANIE2&=~(1<<channel)):(CANIE1&=~(1<<(channel-8)));}

#define CAN_SET_STD_ID_10_4(ident) (((* (Uchar *)(&ident)   )<<5)+((*((Uchar *)(&ident)+1))>>3))
#define CAN_SET_STD_ID_3_0(ident)  ((*((Uchar *)(&ident)+1))<<5)

#define CAN_SET_STD_MSK_10_4(ident) CAN_SET_STD_ID_10_4(ident)
#define CAN_SET_STD_MSK_3_0(ident)  CAN_SET_STD_ID_3_0(ident)

#define CAN_SET_EXT_ID_28_21(ident)(((* (Uchar *)(&ident)   )<<3)+((*((Uchar *)(&ident)+1))>>5))
#define CAN_SET_EXT_ID_20_13(ident)(((*((Uchar *)(&ident)+1))<<3)+((*((Uchar *)(&ident)+2))>>5))
#define CAN_SET_EXT_ID_12_5(ident) (((*((Uchar *)(&ident)+2))<<3)+((*((Uchar *)(&ident)+3))>>5))
#define CAN_SET_EXT_ID_4_0(ident)   ((*((Uchar *)(&ident)+3))<<3)

#define CAN_SET_EXT_MSK_28_21(ident) CAN_SET_EXT_ID_28_21(ident)
#define CAN_SET_EXT_MSK_20_13(ident) CAN_SET_EXT_ID_20_13(ident)
#define CAN_SET_EXT_MSK_12_5(ident) CAN_SET_EXT_ID_12_5(ident)
#define CAN_SET_EXT_MSK_4_0(ident) CAN_SET_EXT_ID_4_0(ident)

#define CAN_SET_CHANNEL(channel) (CANPAGE = (channel << 4))
#define CAN_GET_CHANNEL          (CANPAGE >> 4)

#define ENABLE_CHANNEL_RX      (CANCONCH |= (MSK_CANCONCH_CONF & CH_RxENA))
#define ENABLE_CHANNEL_BUFFER  (CANCONCH |= (MSK_CANCONCH_CONF & CH_RxBENA))
#define ENABLE_CHANNEL_TX      (CANCONCH |= (MSK_CANCONCH_CONF & CH_TxENA))
#define DISABLE_CHANNEL    (CANCONCH &= ~MSK_CANCONCH_CONF)

#define STD_ID(ident) ((unsigned long)ident<<16)

/*_____ T Y P E D E F - D E C L A R A T I O N ________________________________*/
typedef Uchar can_data_t [NB_DATA_MAX];
typedef union{
  Uint32 ext;
  Uint16 std;
  Uchar  tab[4];
} can_id_t;

typedef struct{
  can_id_t id;
  Uchar ctrl;
  Uchar * pt_donne;
} can_msg_t;

typedef enum{
 CHANNEL_0, CHANNEL_1, CHANNEL_2, CHANNEL_3 ,
 CHANNEL_4, CHANNEL_5 ,CHANNEL_6 , CHANNEL_7 ,
 CHANNEL_8, CHANNEL_9 , CHANNEL_10, CHANNEL_11, 
 CHANNEL_12, CHANNEL_13, CHANNEL_14, NO_CHANNEL
} channel_t;

typedef enum { 
  CONF_DLC_0, CONF_DLC_1, CONF_DLC_2, CONF_DLC_3, 
  CONF_DLC_4, CONF_DLC_5, CONF_DLC_6, CONF_DLC_7, CONF_DLC_8
} dlc_t;


#define conf_rx conf
#define conf_tx conf


/*_____ P R O T O T Y P E S - D E C L A R A T I O N __________________________*/

extern can_id_t   can_rx_filt, can_rx_msk;
extern can_id_t   can_tx_id;
extern Uchar * pt_candata_tx; 
extern can_msg_t * pt_st_can_rx;

extern bdata Uchar conf;

extern void CanSetBRP  (Uchar);
extern void CanSetSJW  (Uchar);
extern void CanSetPRS  (Uchar);
extern void CanSetPHS2 (Uchar);
extern void CanSetPHS1 (Uchar);

extern Uchar FindFirstChIt (void);
#define NO_CHANNEL  0xFF


                                                            
extern void RazAllMailbox (void);

extern void WaitTX (Uchar num_channel);
extern void ConfChannel_Rx();
extern void SendCanMsg ();

extern void ReadCanMsg (Uchar nextconf);
/* constant for next configuration in ReadCanMsg function. */

#define CHANNEL_DISABLE			0x01
#define CHANNEL_RX_ENABLE		0x02
#define CHANNEL_RXB_ENABLE		0x04



#endif /* _CAN_LIB_H_ */
