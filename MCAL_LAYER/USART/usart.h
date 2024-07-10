/* 
 * File:   usart.h
 * Author: Rahim Mohamed
 *
 * Created on June 28, 2024, 1:45 PM
 */

#ifndef USART_H
#define	USART_H

/*section : Includes  */

#include "../xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "usart_cfg.h"

/*section : Macro Declaration  */

/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0
/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/*----------------------------------Transmitter------------------------------------*/
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/*----------------------------------Receiver------------------------------------*/
/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0

/*----------------------------------Error------------------------------------*/

/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0



/*section : Macro Functions Declaration  */


/*-------------------------------------------TXSTA------------------------------------------*/

#define SET_MASTER_MODE_CLK()           (TXSTAbits.CSRC=1) // used in Synchrouns Mode & ignored in Asynchronous mode : clock generated internally from BRG
#define SET_SLAVE_MODE_CLK()            (TXSTAbits.CSRC=0) // used in Synchrouns Mode & ignored in Asynchronous mode : clock from external source

#define SET_9BITs_TRANSMISSION()        (TXSTAbits.TX9=1)
#define SET_8BITs_TRANSMISSION()        (TXSTAbits.TX9=0)

#define ENABLE_TRANSMITER_BITs()        (TXSTAbits.TXEN=1)
#define DISABLE_TRANSMITER_BITs()       (TXSTAbits.TXEN=0)

#define SET_SYNC_MODE()                 (TXSTAbits.SYNC=1)
#define SET_ASYNC_MODE()                (TXSTAbits.SYNC=0)

#define SET_HIGH_BAUD_RATE_SPEED()      (TXSTAbits.BRGH=1) // Not used in synchrouns Mode
#define SET_LOW_BAUD_RATE_SPEED()       (TXSTAbits.BRGH=0) // Not used in synchrouns Mode


/*-------------------------------------------RCSTA------------------------------------------*/

#define ENABLE_SERIAL_PORT()        (RCSTAbits.SPEN=1)
#define DISABLE_SERIAL_PORT()       (RCSTAbits.SPEN=0)

#define SET_9BITs_RECEIVER()        (RCSTAbits.RX9=1)
#define SET_8BITs_RECEIVER()        (RCSTAbits.RX9=0)

#define ENABLE_RECEIVER_BITs()      (RCSTAbits.CREN=1)
#define DISABLE_RECEIVER_BITs()     (RCSTAbits.CREN=0)


/*-------------------------------------------BAUDCON------------------------------------------*/

#define SET_16BITs_BAUD_RATE_GEN()        (BAUDCONbits.BRG16=1)
#define SET_8BITs_BAUD_RATE_GEN()         (BAUDCONbits.BRG16=0)



/*section : Data Type Declaration  */

typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
    priority_t usart_tx_int_priority;
	uint_8 usart_tx_enable : 1;
	uint_8 usart_tx_interrupt_enable : 1;
	uint_8 usart_tx_9bit_enable : 1;
    uint_8 usart_tx_reserved : 5;
}usart_tx_cfg_t;

typedef struct{
    priority_t usart_rx_int_priority;
	uint_8 usart_rx_enable : 1;
	uint_8 usart_rx_interrupt_enable : 1;
	uint_8 usart_rx_9bit_enable : 1;
    uint_8 usart_rx_reserved : 5;
}usart_rx_cfg_t;

typedef union{
	struct{
		uint_8 usart_tx_reserved : 6;
		uint_8 usart_ferr : 1;
		uint_8 usart_oerr : 1;
	};
	uint_8 status;
}usart_error_status_t;

typedef struct{
    uint_32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
     usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t error_status;
	void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;

/*section :  Functions Declaration  */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint_8 *_data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint_8 *_data);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint_8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint_8 *_data, uint_16 str_len);
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint_8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint_8 *_data, uint_16 str_len);
#endif	/* USART_H */

