/* 
 * File:   usart.c
 * Author: Rahim Mohamed
 *
 * Created on June 28, 2024, 1:45 PM
 */
#include "usart.h"
/******************************************************************************************************/

#if EUSART_TX_INTERRUPT_ENABLE  == 1
    static void (*EUSART_TxInterruptHandler)(void) = NULL;
#endif
#if EUSART_RX_INTERRUPT_ENABLE  == 1
    static void (*EUSART_RxInterruptHandler)(void) = NULL;
    static void (*EUSART_FramingErrorHandler)(void) = NULL;
    static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif    



static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);

/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
     if (NULL == _eusart){
        ret=E_NOT_OK;
    }
    else{ 
         
     DISABLE_SERIAL_PORT();
     TRISCbits.RC7 = 1;                      /* RX : Input Configuration as needed */
     TRISCbits.RC6 = 1;                      /* TX : Input Configuration as needed */
     EUSART_Baud_Rate_Calculation(_eusart); 
     EUSART_ASYNC_TX_Init(_eusart);
     EUSART_ASYNC_RX_Init(_eusart);   
     ENABLE_SERIAL_PORT();    
         
    }
    return ret;
}

/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart){
    
     Std_ReturnType ret = E_OK;
     if (NULL == _eusart){
        ret=E_NOT_OK;
    }
    else{    
         DISABLE_SERIAL_PORT();
    }
    return ret;
    
}
/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint_8 *_data){
    
     Std_ReturnType ret = E_OK;
     if (NULL == _data){
        ret=E_NOT_OK;
    }
    else{  
    while(!PIR1bits.RCIF);
     *_data =RCREG ;   
    }
    return ret;
    
}

/******************************************************************************************************/
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint_8 *_data){
    
    Std_ReturnType ret = E_NOT_OK;
    if(1 == PIR1bits.RCIF){
        *_data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
    
}

/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_RX_Restart(void){
    DISABLE_RECEIVER_BITs();
    ENABLE_RECEIVER_BITs();
}

/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint_8 _data){
    
     Std_ReturnType ret = E_OK;
     if (0 == _data){
        ret=E_NOT_OK;
    }
    else{     
         
    while(!TXSTAbits.TRMT);
    #if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();
    #endif
    TXREG = _data;
         
    }
    return ret;
    
}
/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint_8 *_data, uint_16 str_len){
    uint_16 counter=0;
     Std_ReturnType ret = E_OK;
     if (NULL == _data){
        ret=E_NOT_OK;
    }
    else{  
         
      for(counter=0;counter<str_len;counter++){
        EUSART_ASYNC_WriteByteBlocking(_data[counter]);  
      }   
    }
    return ret;
    
}
/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint_8 _data){
    
     Std_ReturnType ret = E_OK;
     if (0 == _data){
        ret=E_NOT_OK;
    }
    else{     
    }
    return ret;
    
}

/******************************************************************************************************/

Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint_8 *_data, uint_16 str_len){
    
     Std_ReturnType ret = E_OK;
     if (NULL == _data){
        ret=E_NOT_OK;
    }
    else{     
    }
    return ret;
    
}


/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart){
    float temp_boad_rate=0;
   switch(_eusart->baudrate_gen_gonfig){
       case BAUDRATE_ASYN_8BIT_lOW_SPEED:
           SET_ASYNC_MODE(); // SYNC =0 : Asynchronous Mode 
           SET_LOW_BAUD_RATE_SPEED(); // BRGH =0 : low speed baud rate
           SET_8BITs_BAUD_RATE_GEN(); // BRG16=0 : 8 bit baud rate gen
           temp_boad_rate=  ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1;
           break;
       case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
           SET_ASYNC_MODE(); // SYNC =0 : Asynchronous Mode 
           SET_HIGH_BAUD_RATE_SPEED(); // BRGH =1 : HIGH speed baud rate
           SET_8BITs_BAUD_RATE_GEN(); // BRG16=0 : 8 bit baud rate gen
           temp_boad_rate= ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
           break;
       case BAUDRATE_ASYN_16BIT_lOW_SPEED:
           SET_ASYNC_MODE(); // SYNC =0 : Asynchronous Mode 
           SET_LOW_BAUD_RATE_SPEED(); // BRGH =0 : LOW speed baud rate
           SET_16BITs_BAUD_RATE_GEN(); // BRG16=1 : 16 bit baud rate gen
           temp_boad_rate=((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
           break;
       case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
           SET_ASYNC_MODE(); // SYNC =0 : Asynchronous Mode 
           SET_HIGH_BAUD_RATE_SPEED(); // BRGH =1 : LOW speed baud rate
           SET_16BITs_BAUD_RATE_GEN(); // BRG16=1 : 16 bit baud rate gen
           temp_boad_rate= ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
           break;
       case BAUDRATE_SYN_8BIT:
           SET_SYNC_MODE(); // SYNC =1 : synchronous Mode 
           SET_8BITs_BAUD_RATE_GEN(); // BRG16=0 : 8 bit baud rate gen
           temp_boad_rate= ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
           break;
       case BAUDRATE_SYN_16BIT:
           SET_SYNC_MODE(); // SYNC =1 : synchronous Mode 
           SET_16BITs_BAUD_RATE_GEN(); // BRG16=1 : 16 bit baud rate gen
           temp_boad_rate=  ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
           break;    
   } 
     SPBRG = (uint_8)((uint_32)temp_boad_rate);
    SPBRGH = (uint_8)(((uint_32)temp_boad_rate) >> 8);
}


/************************************************************************************************************************/

static void EUSART_ASYNC_TX_Init(const usart_t *_eusart){

    if (EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        ENABLE_TRANSMITER_BITs();
        /*-------------------------------- EUSART Transmit Interrupt Configuration ------------------------------------*/
        if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE==_eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            EUSART_TX_InterruptEnable();
            EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
         /* Configure Interrupt */
         #if EUSART_TX_INTERRUPT_ENABLE  == 1
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
         #endif
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
           INTERRUPT_PriorityLevels_Enable();
            if(HIGH_priority == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalHighPriority_Enable();
                EUSART_TX_Interrupt_HighPrioritySet();
            }
            else if(LOW_priority  == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalLowPriority_Enable();
                EUSART_TX_Interrupt_LowPrioritySet();
            }
            else{ /* Nothing */ }
         #endif
         #endif 
        
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE==_eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            EUSART_TX_InterruptDisable(); 
        }
         else{/* Nothing */}
         /*--------------------------------  EUSART  9-Bit Transmit Configuration ------------------------------------*/
        if (EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE==_eusart->usart_tx_cfg.usart_tx_9bit_enable){
           SET_9BITs_TRANSMISSION();
        }
        else if (EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE==_eusart->usart_tx_cfg.usart_tx_9bit_enable){
            SET_8BITs_TRANSMISSION();
        }
         else{/* Nothing */}
        
    }
    else{/* Nothing */}
    
}

/************************************************************************************************************************/

static void EUSART_ASYNC_RX_Init(const usart_t *_eusart){
    
    if (EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        ENABLE_RECEIVER_BITs();
        /*-------------------------------- EUSART Receiver Interrupt Configuration ------------------------------------*/
        if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE==_eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            EUSART_RX_InterruptEnable();
        EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;  
       /* Configure Interrupt */
         #if EUSART_RX_INTERRUPT_ENABLE  == 1
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
         INTERRUPT_GlobalInterrupts_Enable();
         INTERRUPT_peripheralInterrupt_Enable();
         #endif
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INERRUPT_FEAUTURE_ENABLE
           INTERRUPT_PriorityLevels_Enable();
            if(HIGH_priority == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalHighPriority_Enable();
                EUSART_RX_Interrupt_HighPrioritySet();
            }
            else if(LOW_priority  == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalLowPriority_Enable();
                EUSART_RX_Interrupt_LowPrioritySet();
            }
            else{ /* Nothing */ }
         #endif
         #endif        
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE==_eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            EUSART_RX_InterruptDisable(); 
        }
         else{/* Nothing */}
         /*--------------------------------  EUSART  9-Bit Receive Configuration ------------------------------------*/
        if (EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE==_eusart->usart_rx_cfg.usart_rx_9bit_enable){
           SET_9BITs_RECEIVER();
        }
        else if (EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE==_eusart->usart_rx_cfg.usart_rx_9bit_enable){
           SET_8BITs_RECEIVER();
        }
         else{/* Nothing */}
        
    }
    else{/* Nothing */}
    
}

void EUSART_TX_ISR(void){
    EUSART_TX_InterruptDisable();
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }else { /* Nothing */}
}

void EUSART_RX_ISR(void){
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }else { /* Nothing */}
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }else { /* Nothing */}
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }else { /* Nothing */}
}