/* 
 * File:   eeprom.h
 * Author: gaming3
 *
 * Created on February 29, 2024, 8:53 PM
 */

#include "eeprom.h"

/**********************************************************************************************************************/
Std_ReturnType Data_EEPROM_WriteByte (uint_16 bAdd, uint_16 bData){
    
       Std_ReturnType ret = E_OK;
       // read interrupt status disable or enable
       uint_8 interrupt_status = INTCONbits.GIE;
       // update the address registers
       EEADRH = (uint_8) ((bAdd >> 8) &0x03);
       EEADRH = (uint_8) (bAdd & 0xFF);
       //update data register
       EEDATA=bData;
       // select access data EEPROM memory
       EECON1bits.EEPGD=0;
       EECON1bits.CFGS=0;
       //Allows write cycles to Flash programs /data EEPROM
        EECON1bits.WREN=1;
        //disable all global interrupts 
        INTERRUPT_GlobalInterrupts_Disable();
       //write the required sequence :0x55 -> 0xAA
        EECON2 = 0x55;
        EECON2 = 0xAA;
       //Initiates a data EEPROM erase/Write Cycle
        EECON1bits.WR=1;
       //Wait for write to complete
        while (EECON1bits.WR);
       //Inhibits write cycles to flash program/data EEPROM
          EECON1bits.WREN=0;   
       //Restore the interrupt status
          INTCONbits.GIE=interrupt_status;
    return ret;
    
}
/************************************************************************************************************************/
Std_ReturnType Data_EEPROM_ReadByte (uint_16 bAdd, uint_16 *bData){
    
      Std_ReturnType ret = E_OK;
    if (NULL == bData ){
        ret=E_NOT_OK;
    }
    else{
    // update the address registers
       EEADRH = (uint_8) ((bAdd >> 8) &0x03);
       EEADRH = (uint_8) (bAdd & 0xFF);
    // select access data EEPROM memory  
       EECON1bits.EEPGD=0;
       EECON1bits.CFGS=0;
    //Initiates a data EEPROM read Cycle 
       EECON1bits.RD=1;
       NOP();
       NOP();
    // Return data  
     *bData=EEDATA;  
    }
    return ret;
}