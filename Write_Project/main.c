/*
 * main.c
 *
 *  Created on: Jan 27, 2021
 *      Author: yehia
 */

#include <avr/pgmspace.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "LED_interface.h"
#include "PEEPROM_interface.h"

#include "M_help.h"
#include "M_after.h"
#include "M_morn.h"
#include "M_bye.h"
#include "M_hello.h"
#include "M_hung.h"
#include "M_thirst.h"

#define HELP_OFFSET				0
#define HELP_COUNTER			3947-1

#define HUNGRY_OFFSET			3947
#define HUNGRY_COUNTER			7523-1

#define THIRSTY_OFFSET			7523
#define THIRSTY_COUNTER			11238-1

#define BYE_OFFSET				11238
#define BYE_COUNTER				14164-1

#define HELLO_OFFSET			14164
#define HELLO_COUNTER			16904-1

#define MORN_OFFSET				16904
#define MORN_COUNTER			20433-1

#define AFTER_OFFSET			20433
#define AFTER_COUNTER			24241-1

#define WRITE_PORT				PORT_C

void main(void)
{
	u16 Local_u16Counter=0;
	LED_t Local_LED_tIndicationLed = {LED_PORTA, LED_PIN5, LED_u8ACTIVE_HIGH};

	PORT_voidInit();

	LED_voidLedOn(&Local_LED_tIndicationLed);

	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+HELP_OFFSET, pgm_read_byte(&Male_help_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+HELP_OFFSET)) == (pgm_read_byte(&Male_help_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(HELP_COUNTER-HELP_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+HUNGRY_OFFSET, pgm_read_byte(&Male_hungry_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+HUNGRY_OFFSET)) == (pgm_read_byte(&Male_hungry_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(HUNGRY_COUNTER-HUNGRY_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+THIRSTY_OFFSET, pgm_read_byte(&Male_thirsty_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+THIRSTY_OFFSET)) == (pgm_read_byte(&Male_thirsty_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(THIRSTY_COUNTER-THIRSTY_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+BYE_OFFSET, pgm_read_byte(&Male_Bye_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+BYE_OFFSET)) == (pgm_read_byte(&Male_Bye_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(BYE_COUNTER-BYE_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+HELLO_OFFSET, pgm_read_byte(&Male_hello_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+HELLO_OFFSET)) == (pgm_read_byte(&Male_hello_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(HELLO_COUNTER-HELLO_OFFSET))
			break;
	}
		Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+MORN_OFFSET, pgm_read_byte(&Male_Morning_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+MORN_OFFSET)) == (pgm_read_byte(&Male_Morning_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(MORN_COUNTER-MORN_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+AFTER_OFFSET, pgm_read_byte(&Male_Afternoon_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+AFTER_OFFSET)) == (pgm_read_byte(&Male_Afternoon_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(AFTER_COUNTER-AFTER_OFFSET))
			break;
	}

	LED_voidLedOff(&Local_LED_tIndicationLed);

	while(1);

}

