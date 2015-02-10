/*C*****************************************************************************
* FILE_NAME         : Can_lib.c                                             
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : BERTHY JS                                             
* FILE_CREATION_DATE: 27/09/99                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE: provide low level functions for CAN controller   
*
* Timing with 12 MHz oscillator
*
* - CANSetBRP    	:  14 us                                 
* - CANSetSJW       :  18 us                             
* - CANSetPRS       :  16 us                                 
* - CANSetPHS2      :  17 us                                                                               
* - CANSetPHS1      :  16 us                                                        
* - FindFirstChIt   :  24 us max(it on channel14)                                                       
* - ConfChannel_Rx  : 110 us max(ide with mask),  59 us max(std with mask)                                                       
* - SendCanMsg      : 333 us max(ide, 8 data)  , 306 us max(std, 8 data)                                                        
* - ReadCanMsg_Rx   : 392 us max(ide, 8data) ,   326 us max(std, 8 data)                                                         
* - RazAllMailbox	: 890 us
******************************************************************************/

/*_____ I N C L U D E - F I L E S ____________________________________________*/


#include "config.h"
#include "can_lib.h"


/*_____ G L O B A L S ________________________________________________________*/

/* variables used by ConfChannel_Rx. */
can_id_t   can_rx_filt, 
           can_rx_msk;

/* variables used by SendCanMsg. */
Uchar * pt_candata_tx; 
can_id_t can_tx_id;
/* variables used by ReadCanMsg. */
can_msg_t * pt_st_can_rx;


/* bit decalaration used by SendCanMsg and ConfChannel_rx 
*  this variable is redeclared in conf_rx and conf_tx.
* -------------------------------------------------------*/
bdata Uchar conf;
Sbit( msk_ide, conf, 7);  /* just for TX      */
Sbit( msk_rtr, conf, 6);  /* just for RX      */
Sbit( rtr    , conf, 5);  /* commun Rx and TX */
Sbit( ide    , conf, 4);  /* commun RX and TX */
Sbit( buffer , conf, 0);  /* just for TX      */


/* bit decalaration used by ReadCanMsg 
*------------------------------------
* The declaration of NEW_CONF depend of declaration below
* #define CHANNEL_DISABLE		0x01 -> bit0 of b_var_read
* #define CHANNEL_RX_ENABLE		0x02 -> bit1 of b_var_read
* #define CHANNEL_RXB_ENABLE	0x04 -> bit2 of b_var_read
*/
bdata Uchar b_var_read;
Sbit( bit_read_7, b_var_read, 7);
Sbit( bit_read_6, b_var_read, 6);
Sbit( bit_read_5, b_var_read, 5);
Sbit( bit_read_4, b_var_read, 4);
Sbit( bit_read_3, b_var_read, 3);
Sbit( bit_read_2, b_var_read, 2);
Sbit( bit_read_1, b_var_read, 1);
Sbit( bit_read_0, b_var_read, 0);

#define NEW_CONF_CH_DISABLE 	bit_read_0
#define NEW_CONF_CH_RX_ENABLE 	bit_read_1
#define NEW_CONF_CH_RXB_ENABLE 	bit_read_2


/* bit decalaration used by FindFirstChIt and fct_can_it
*-------------------------------------------------------*/
bdata Uchar bit_var;
Sbit( bit_7, bit_var, 7);
Sbit( bit_6, bit_var, 6);
Sbit( bit_5, bit_var, 5);
Sbit( bit_4, bit_var, 4);
Sbit( bit_3, bit_var, 3);
Sbit( bit_2, bit_var, 2);
Sbit( bit_1, bit_var, 1);
Sbit( bit_0, bit_var, 0);

#define IT_TXOK bit_6
#define IT_RXOK bit_5


/*_____ P R I V A T E - F U N C T I O N S - D E C L A R A T I O N ____________*/


/*_____ L O C A L S __________________________________________________________*/


/*_____ P U B L I C - F U N C T I O N S ______________________________________*/


/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/


/*F****************************************************************************
* FUNCTION_NAME: RazAllMailbox                                                  
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 13/10/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Raz mailbox, status and control register     
* FUNCTION_INPUTS : void                                                          
* FUNCTION_OUTPUTS: void                                                       
******************************************************************************/
void RazAllMailbox (void)
{
  Uchar num_channel, num_data;

  for (num_channel = 0; num_channel < NB_CHANNEL; num_channel++)
  {
    CANPAGE  = num_channel << 4;
    CANCONCH = 0;
    CANSTCH  = 0;
    CANIDT1  = 0;
    CANIDT2  = 0;
    CANIDT3  = 0;
    CANIDT4  = 0;
    CANIDM1  = 0;
    CANIDM2  = 0;
    CANIDM3  = 0;
    CANIDM4  = 0;
    for (num_data = 0; num_data < NB_DATA_MAX; num_data++)
    {
      CANMSG = 0;
    }
  }

}


/*F****************************************************************************
* FUNCTION_NAME: CanSetBRP                                                  
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 27/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Initialise the Prescaler for CAN Controler baudrate     
*                    with value pasted in parameter.                         
*                    Tscl = 2*(prescaler +1) / Fin                           
*                    -----------------------------                            
* FUNCTION_INPUTS : Uchar prescaler : CAN_BAUDRATE_MIN to CAN_BAUDRATE_MAX                    
* FUNCTION_OUTPUTS: void                                                         
******************************************************************************/
void CanSetBRP (Uchar prescaler)
{

  if ((prescaler <= CAN_PRESCALER_MAX) &&
      (prescaler >= CAN_PRESCALER_MIN)   )
  {
    CANBT1 = prescaler << 1;
  }

}


/*F***************************************************************************
* FUNCTION_NAME: CanSetSJW                                                  
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 27/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Initialise the Re_synchronization jump width for CAN    
*                    Controler baudrate with value pasted in parameter.      
*                      Tsjw = Tscl * (sjw + 1)                                
*                      -----------------------                               
* FUNCTION_INPUTS : Uchar sjw : CAN_SJW_MIN to CAN_SJW_MAX                                    
* FUNCTION_OUTPUTS: void                                                        
******************************************************************************/
void CanSetSJW (Uchar sjw)
{
 
  if ((sjw <= CAN_SJW_MAX) &&
      (sjw >= CAN_SJW_MIN)   )
  {
    CANBT2 &= ~MSK_CANBT2_SJW;	/* RAZ of field sjw.  */
    CANBT2 |= (sjw << 5);
  }

}



/*F****************************************************************************
* FUNCTION_NAME: CanSetPRS                                                  
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 27/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Initialise the Programation time segment for CAN        
*                    Controler with value pasted in parameter.               
*                      Tprs = Tscl * (prs + 1)                                
*                      -----------------------                               
* FUNCTION_INPUTS : Uchar prs : CAN_PRS_MIN to CAN_PRS_MAX                                    
* FUNCTION_OUTPUTS: void                                                         
******************************************************************************/
void CanSetPRS (Uchar prs)
{

  if ((prs <= CAN_PRS_MAX) &&
      (prs >= CAN_PRS_MIN)   )
  {
    CANBT2 &= ~MSK_CANBT2_PRS;   /* RAZ of field prs.  */
    CANBT2 |= (prs << 1);
  }

}


/*F***************************************************************************
* FUNCTION_NAME: CanSetPHS2                                                 
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 27/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Initialise the Phase segment 2 for CAN Controller       
*                    with value pasted in parameter.                         
*                      Tphs2 = Tscl * (phs2 + 1)                              
*                      -------------------------                             
* FUNCTION_INPUTS : Uchar phs2: CAN_PHS2_MIN to CAN_PHS2_MAX                                 
* FUNCTION_OUTPUTS: void                                                         
******************************************************************************/
void CanSetPHS2 (Uchar phs2)
{
  if ((phs2 <= CAN_PHS2_MAX) &&
      (phs2 >= CAN_PHS2_MIN)   )
  {
    CANBT3 &= ~MSK_CANBT3_PHS2;  /* RAZ of field PHS2.  */
    CANBT3 |= (phs2 << 4);
  }

}



/*F****************************************************************************
* FUNCTION_NAME: CanSetPHS1                                                 
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 27/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Initialise the Phase segment 1 for CAN Controller       
*                    with value pasted in parameter.                         
*                      Tphs1 = Tscl * (phs1 + 1)                              
*                      -------------------------                             
* FUNCTION_INPUTS : Uchar phs1 : CAN_PHS1_MIN to CAN_PHS1_MAX                                 
* FUNCTION_OUTPUTS: void                                                        
******************************************************************************/
void CanSetPHS1 (Uchar phs1)
{
  if ((phs1 <= CAN_PHS1_MAX) &&
      (phs1 >= CAN_PHS1_MIN)   )
  {
    CANBT3 &= ~MSK_CANBT3_PHS1;   /* RAZ field of phs1.  */
    CANBT3 |= (phs1 << 1);
  }

}


/*F**************************************************************************
* FUNCTION_NAME: ConfChannel_Rx                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 28/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Configure the channel in reception,
*        The identifier filtered and mask are initialized with the 
*        value contain in global variables can_rx_id and can_rx_msk.     
*        The configuration is defined in globale variable conf_rx.                   
*                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                    
*----------------------------------------------------------------------------
* GLOBAL VARIABLES USED :
*	- conf_rx
*	- can_rx_filt
*	- can_rx_msk
******************************************************************************
* The variable conf_rx must contain information:                                   
*    - on ide:
*           standart (CONF_NOIDE) or 
*           extended (CONF_IDE)                     
*    - on ide mask, 
*           no mask on ide bit(CONF_NOMSK_IDE) or
*           mask on ide bit   (CONF_MSK_IDE) 
*    - on rtr:
*           data frame   (CONF_NORTR) or 
*           remote frame (CONF_RTR)                     
*    - on rtr mask, 
*           no mask on rtr bit(CONF_NOMSK_RTR) or 
*           mask on rtr bit   (CONF_MSK_RTR) 
*    - on buffer mode
*           channel is for the buffer mode (CONF_BUFFER) or
*           channel is not for buffer mode (CONF_NOBUFFER) 
*
* Exemple of configuration:                                                                   
* ------------------------                                                                   
* conf_rx = CONF_IDE | CONF_NOMSK_IDE | CONF_NORTR | 
*           CONF_NOMSK_RTR | CONF_NOBUFFER                                       
*                                                                            
******************************************************************************
* NOTE:                                                                      
*     It's very important to make sure that channel is free.                 
*     No verification are perform by this function.                          
*     The corresponding channel must selected before called this function
*
*     When conf_rx = 0 -> CONF_NOIDE | CONF_NOMSK_IDE | CONF_NORTR |
*                         CONF_NOMSK_RTR | NO_BUFFER 
*
* Exemple of use:
*---------------
*
*  can_rx_filt.ext = 0x5555555;
*  can_rx_msk.ext  = 0x00;
*  conf_rx         = CONF_IDE|CONF_MSK_IDE|CONF_NOBUFFER;
*  CAN_SET_CHANNEL(CHANNEL_1);
*  ConfChannel_Rx();
*
******************************************************************************/
void ConfChannel_Rx()
{


  CANSTCH  = 0x00;               
  CANCONCH = 0x00;            

  if (ide == TRUE)
  {                                /* identifier = 29 bits.            */  
    CANIDT1 = CAN_SET_EXT_ID_28_21 (can_rx_filt.ext);
    CANIDT2 = CAN_SET_EXT_ID_20_13 (can_rx_filt.ext);
    CANIDT3 = CAN_SET_EXT_ID_12_5  (can_rx_filt.ext);
    CANIDT4 = CAN_SET_EXT_ID_4_0   (can_rx_filt.ext);

    CANIDM1 = CAN_SET_EXT_MSK_28_21 (can_rx_msk.ext);
    CANIDM2 = CAN_SET_EXT_MSK_20_13 (can_rx_msk.ext);
    CANIDM3 = CAN_SET_EXT_MSK_12_5  (can_rx_msk.ext);
    CANIDM4 = CAN_SET_EXT_MSK_4_0   (can_rx_msk.ext);
    CANCONCH|= MSK_CANCONCH_IDE;  /* set bit ide in CANCONCH.  */
  }
  else                        /* In Standart mode (ide = B_FALSE), */
  {                           /* identifier = 11bits.              */
    CANIDT1 = CAN_SET_STD_ID_10_4 (can_rx_filt.std);
    CANIDT2 = CAN_SET_STD_ID_3_0 (can_rx_filt.std);

    CANIDM1 = CAN_SET_STD_MSK_10_4 (can_rx_msk.std);
    CANIDM2 = CAN_SET_STD_MSK_3_0 (can_rx_msk.std);
    CANIDM4 = 0;
  }

  if (rtr == TRUE)
  {
    CANIDT4 |= MSK_CANIDT4_RTRTAG;   /* set bit rtr in CANIDT4.   */   
  }
  else
  {
    CANIDT4 &=~MSK_CANIDT4_RTRTAG;   /* clear bit rtr in CANIDT4. */
  }

  if (msk_rtr == TRUE)
  {
    CANIDM4 |= MSK_CANIDM4_RTRMSK;	 /* set bit rtr in CANIDM4.   */ 
  }
  
  if (msk_ide == TRUE)
  {
    CANIDM4 |= MSK_CANIDM4_IDEMSK;   /* set bit ide in CANIDM4.   */
  }

  if (buffer == TRUE)
  {
    ENABLE_CHANNEL_BUFFER; /* Buffer Reception enabled.*/
  }
  else
  {
    ENABLE_CHANNEL_RX; /* Reception enabled.*/
  }

  CANCONCH |= 0x08;

}

/*F***************************************************************************
* FUNCTION_NAME:  SendCanMsg                                                
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 28/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Send message        
*        The identifier to send is declared in the globale variable can_id_tx,
*        data to transmit are declared in the globale variable pt_candata_tx  
*        The configuration is defined in globale variable conf_tx.                   
* FUNCTION_INPUTS : void                                                        
* FUNCTION_OUTPUTS: void                                                        
*----------------------------------------------------------------------------
* GLOBAL VARIABLES USED :
*	- conf_tx
*	- pt_candata_tx
*	- can_tx_id
******************************************************************************
* The variable conf_tx must contain information:                                   
*    - on ide:
*           standart(NOT_IDE) or 
*           extended (IDE)                     
*    - on rtr:
*           remote frame(RTR) or 
*           data frame(NO_RTR)       
*    - on dlc: size of data dlc_t.
*
* Exemple of declaration:                          
* ---------------------- 
*                                                                  
* conf_tx = IDE | NO_RTR | DLC_6 
*                                      
******************************************************************************                                                                            
* NOTE:                                                                      
*     It's very important to make sure that channel is free.                 
*     No verification are perform by this function.                          
*
* Exemple of use:
* ---------------
*
*  CAN_SET_CHANNEL(CHANNEL_7);
*  canid_tx.std = frame1.id.std;
*  conf_tx      = frame1.ctrl;
*  pt_candata_tx= frame1.pt_donne;
*  CANIE2 |= (1 << CHANNEL_7);
*  SendCanMsg();
******************************************************************************/
void SendCanMsg (void)
{
  Uchar  dlc, i;


  CAN_IT_DISABLE;
 
  CANSTCH  = 0x00;
  CANCONCH = conf;
  
  if (ide == TRUE)
  {
    CANIDT1 = CAN_SET_EXT_ID_28_21 (can_tx_id.ext);
    CANIDT2 = CAN_SET_EXT_ID_20_13 (can_tx_id.ext);
    CANIDT3 = CAN_SET_EXT_ID_12_5  (can_tx_id.ext);
    CANIDT4 = CAN_SET_EXT_ID_4_0   (can_tx_id.ext);
  }
  else
  {
    CANIDT1 = CAN_SET_STD_ID_10_4 (can_tx_id.std);
    CANIDT2 = CAN_SET_STD_ID_3_0  (can_tx_id.std);
  }
/* load data to tx. */
  dlc = (conf & MSK_CTRL_DLC);  
  for (i=dlc; i!=0; i--)
  {
    CANMSG = *pt_candata_tx++;
  }

  ENABLE_CHANNEL_TX;
  CAN_IT_ENABLE;


}

/*F***************************************************************************
* FUNCTION_NAME: ReadCanMsg                                                 
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 28/09/99                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Copy message received on num_channel in structure       
*                   of type st_can_msg_t, and configured the channel with the
*                   new configuration given by next_conf, past in parameter                                   
* FUNCTION_INPUTS : Uchar next_conf: 
*                        - CHANNEL_DISABLE    
*                        - CHANNEL_RX_ENABLE (re-enable the channel in reception)
*                        - CHANNEL_RXB_ENABLE(re-enable the channel 
*                                             in buffer mode)                                                 
* FUNCTION_OUTPUTS: void                                                         
*----------------------------------------------------------------------------
* GLOBAL VARIABLES USED :
*	- conf_rx
*	- pt_st_can_rx
******************************************************************************
* NOTE:                                                                      
******************************************************************************/
void ReadCanMsg (Uchar next_conf)
{
  Uchar * pt_local;
  Uchar dlc, i;


  pt_st_can_rx->ctrl = CANCONCH;

  conf_rx = CANCONCH;

  if(ide)
  {
    pt_st_can_rx->id.tab[0] = CANIDT1 >> 3;   
    pt_st_can_rx->id.tab[1] = (CANIDT1 << 5) | (CANIDT2 >> 3);    
    pt_st_can_rx->id.tab[2] = (CANIDT2 << 5) | (CANIDT3 >> 3);    
    pt_st_can_rx->id.tab[3] = (CANIDT3 << 5) | (CANIDT4 >> 3);   
  }
  else
  {
    pt_st_can_rx->id.std = (CANIDT1 << 3) | (CANIDT2 >> 5);
  }

  pt_local = pt_st_can_rx->pt_donne;
  dlc      = (conf_rx & MSK_CTRL_DLC);  
  for (i=dlc; i!=0; i--)
  {
    *pt_local++ = CANMSG;
  }


/*---------- New configuration for this channel. */
  b_var_read = next_conf;
  if (NEW_CONF_CH_DISABLE)
  {
    CANCONCH |= (MSK_CANCONCH_CONF & CH_DISABLE); /* Reception disable.*/
  }
  else if(NEW_CONF_CH_RX_ENABLE) 
  {
    CANCONCH |= (MSK_CANCONCH_CONF & CH_RxENA); /* Reception enable.*/
  }
  else /* CHANNEL_RXB_ENABLE */
  {
    CANCONCH |= (MSK_CANCONCH_CONF & CH_RxBENA); /* Buffer enable.*/
  }

}




/*F***************************************************************************
* FUNCTION_NAME:  FindFirstChIt                                              
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  :                                               
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: This function return the first channel with an interrupt
*                   request. The big priority start with the lowest channel 
*                   value (CHANNEL_0). 
* FUNCTION_INPUTS : void                 
* FUNCTION_OUTPUTS: Uchar num_channel: return the channel number of the first 
*                   it find in CANSIT registers.                                                         
*****************************************************************************
* NOTE:                                                                      
******************************************************************************/
Uchar FindFirstChIt (void)
{
  Uchar num_channel = NO_CHANNEL;


  if (CANSIT2)
  {
    bit_var = CANSIT2;
    if(bit_0)
    {
      num_channel = CHANNEL_0;
    }
    else if (bit_1)
    {
      num_channel = CHANNEL_1;
    }
    else if (bit_2)
    {
      num_channel = CHANNEL_2;
    }
    else if (bit_3)
    {
      num_channel = CHANNEL_3;
    }
    else if (bit_4)
    {
      num_channel = CHANNEL_4;
    }
    else if (bit_5)
    {
      num_channel = CHANNEL_5;
    }
    else if (bit_6)
    {
      num_channel = CHANNEL_6;
    }
    else 
    {
      num_channel = CHANNEL_7;
    }
    
  }
  else if (CANSIT1)
  {
    bit_var = CANSIT1;
    if(bit_0)
    {
      num_channel = CHANNEL_8;
    }
    else if (bit_1)
    {
      num_channel = CHANNEL_9;
    }
    else if (bit_2)
    {
      num_channel = CHANNEL_10;
    }
    else if (bit_3)
    {
      num_channel = CHANNEL_11;
    }
    else if (bit_4)
    {
      num_channel = CHANNEL_12;
    }
    else if (bit_5)
    {
      num_channel = CHANNEL_13;
    }
    else if (bit_6)
    {
      num_channel = CHANNEL_14;
    }
  }

  return(num_channel);
}


/*F***************************************************************************
* FUNCTION_NAME: fct_can_it                                                
*-----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  :                                                  
*-----------------------------------------------------------------------------
* FUNCTION_PURPOSE: function called on can interrupt
*			The first task of this function is to identified whish channel 
*           generate the interrupt, and the second is to identified whish kind
*           of interrupt is generated (rxok, txok, error, buffer full).                                  
* FUNCTION_INPUTS : void                                                        
* FUNCTION_OUTPUTS: void                                                        
******************************************************************************
* NOTE:                                                                      
******************************************************************************/
void fct_can_it (void)
{
  Uchar channel;
  Uchar save_canpage;
  
// Save the courant CANPAGE
  save_canpage = CANPAGE;

  channel = FindFirstChIt();

  if (channel != NO_CHANNEL)
  {
    CAN_SET_CHANNEL(channel);

    bit_var = CANSTCH;

 /* Tx or Rx interrupt*/
    if (IT_RXOK)
    {
#ifdef USER_CAN_FCT_IT_RXOK

      can_fct_it_rxok();

#endif /* USER_CAN_FCT_IT_RXOK */
 
    }
    else if (IT_TXOK)
    {
#ifdef USER_CAN_FCT_IT_TXOK

      can_fct_it_txok();  

#endif /* USER_CAN_FCT_IT_TXOK */

    }
/* Error Analysis */
    if(!IT_RXOK && !IT_TXOK)
    {

#ifdef USER_CAN_FCT_IT_ERROR    

      can_fct_it_error();

#endif /* USER_CAN_FCT_IT_ERROR */

    }
/* Raz all flag */
    CANSTCH = 0x00;
  } 
  else
  {
/* No Channel match with the interrupt => General it*/
#ifdef USER_CAN_FCT_IT_GEN

    can_fct_it_gen();

#endif /* USER_CAN_FCT_IT_GEN */
    CANGIT &= 0xF0;
  } 

// restore the old config
  CANPAGE = save_canpage;
}


/*F***************************************************************************
* FUNCTION_NAME: fct_tim_ovf_it                                                
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  :                                                  
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: function called on ovf_tim                                  
* FUNCTION_INPUTS : void                                                        
* FUNCTION_OUTPUTS: void                                                        
******************************************************************************
* NOTE:                                                                      
/******************************************************************************/
void fct_tim_ovf_it (void)
{
#ifdef USER_CAN_FCT_IT_TIMOVF
 
  can_fct_it_timovf();

#endif /* USER_CAN_FCT_IT_TIMOVF */

  CANGIT &= ~MSK_CANGIT_OVRTIM; 
}



























