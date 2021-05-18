/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     			************/
/************		SWC: PEEPROM			************/
/************		Version: 1.00	 		************/
/************		Date: 2-1-2021 			************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef PEEPROM_INTERFACE_H_
#define PEEPROM_INTERFACE_H_


void PEEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 PEEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

void PPEPROM_voidDisableOutput(void);

#endif
