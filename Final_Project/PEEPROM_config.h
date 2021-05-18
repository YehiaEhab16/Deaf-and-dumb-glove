/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     			************/
/************		SWC: PEEPROM			************/
/************		Version: 1.00	 		************/
/************		Date: 2-1-2021 			************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef PEEPROM_CONFIG_H_
#define PEEPROM_CONFIG_H_


#define PEEPROM_DATA_PORT 			DIO_u8PORTC

#define PEEPROM_CTRL_PORT 			DIO_u8PORTA		//for OE, WE

#define PEEPROM_ADDRESS_PORT1 		DIO_u8PORTB		//for A7 -> A0

#define PEEPROM_ADDRESS_PORT2	 	DIO_u8PORTD		//for A15 ->A8

#define PEEPROM_OE					DIO_u8PIN7
#define PEEPROM_WE					DIO_u8PIN6		// should be output , initial high


#endif
