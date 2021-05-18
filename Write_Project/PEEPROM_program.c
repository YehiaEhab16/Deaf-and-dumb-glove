/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     			************/
/************		SWC: PEEPROM			************/
/************		Version: 1.00	 		************/
/************		Date: 2-1-2021 			************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "PEEPROM_config.h"
#include "PEEPROM_interface.h"
#include "PEEPROM_private.h"

void PEEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte)
{
	DIO_u8SetPortValue(PEEPROM_ADDRESS_PORT1, (u8)Copy_u16LocationAddress);
	DIO_u8SetPortValue(PEEPROM_ADDRESS_PORT2, (u8)(Copy_u16LocationAddress>>8));
	DIO_u8SetPinValue(PEEPROM_CTRL_PORT, PEEPROM_OE, DIO_u8PIN_HIGH);

	DIO_u8SetPortValue(PEEPROM_DATA_PORT, Copy_u8DataByte);

	_delay_ms(10);
	DIO_u8SetPinValue(PEEPROM_CTRL_PORT, PEEPROM_WE, DIO_u8PIN_LOW);
	_delay_us(1);
	DIO_u8SetPinValue(PEEPROM_CTRL_PORT, PEEPROM_WE, DIO_u8PIN_HIGH);
	_delay_ms(10);
}

u8 PEEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress)
{
	u8 Local_u8Data=0, Local_u8Counter, Local_u8EEPROM=0;

	DIO_u8SetPortValue(PEEPROM_ADDRESS_PORT1, (u8)Copy_u16LocationAddress);
	DIO_u8SetPortValue(PEEPROM_ADDRESS_PORT2, (u8)(Copy_u16LocationAddress>>8));
	DIO_u8SetPinValue(PEEPROM_CTRL_PORT, PEEPROM_OE, DIO_u8PIN_LOW);
	
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		DIO_u8GetPinValue(PEEPROM_DATA_PORT, Local_u8Counter, &Local_u8EEPROM);
		if(Local_u8EEPROM==1)
			SET_BIT(Local_u8Data, Local_u8Counter);
		else
			CLR_BIT(Local_u8Data, Local_u8Counter);
	}

	return Local_u8Data;
}

void PPEPROM_voidDisableOutput(void)
{
	DIO_u8SetPinValue(PEEPROM_CTRL_PORT, PEEPROM_OE, DIO_u8PIN_HIGH);
}
