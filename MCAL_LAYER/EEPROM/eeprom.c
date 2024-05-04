/* 
 * File:   eeprom.c
 * Author: gaming3
 *
 * Created on February 29, 2024, 8:53 PM
 */

#include "eeprom.h"

/**********************************************************************************************************************/
Std_ReturnType Data_EEPROM_WriteByte (uint_16 bAdd, uint_16 bData){
    
       Std_ReturnType ret = E_OK;
     uint_8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (uint_8)((bAdd >> 8) & 0x03);
    EEADR = (uint_8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;//0
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;//0
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;//1
    /* Disable all interrupts "General Interrupt" */
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==0
    INTERRUPT_GlobalInterrupts_Disable();
    #endif
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;//1
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;//0
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
    
}
/************************************************************************************************************************/
Std_ReturnType Data_EEPROM_ReadByte (uint_16 bAdd, uint_16 *bData){
    
      Std_ReturnType ret = E_OK;
    if (NULL == bData ){
        ret=E_NOT_OK;
    }
    else{
   /* Update the Address Registers */
        EEADRH = (uint_8)((bAdd >> 8) & 0x03);
        EEADR = (uint_8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP(); /* NOPs may be required for latency at high frequencies */
        NOP(); /* NOPs may be required for latency at high frequencies */
        /* Return data */
        *bData = EEDATA;
        ret = E_OK;
    }
    return ret;
}