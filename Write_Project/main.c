/*
 * main.c
 *
 *  Created on: Jan 27, 2021
 *      Author: yehia
 */

#include <avr/pgmspace.h>


#include "STD_TYPES.h"
#include "util/delay.h"


//#include "Hello.h"
//#include "i'm_Hungry.h"
//#include "please_help_me.h"
//#include "i'm_Thirsty.h"
//#include "GoodBye.h"

#include "hello3.h"
#include "help3.h"
#include "hungry3.h"
#include "bye3.h"
#include "thirsty3.h"

/*#include "hi.h"
#include "bye.h"
#include "Hungry.h"
#include "thank.h"
#include "ex.h"
*/



#include "DIO_interface.h"
#include "PORT_interface.h"

#include "LED_interface.h"
#include "PEEPROM_interface.h"


/*
#define HELLO_OFFSET			0
#define HELLO_COUNTER			2601

#define HUNGRY_OFFSET			2601
#define HUNGRY_COUNTER			5202

#define HELP_OFFSET				5202
#define HELP_COUNTER			8175

#define THIRSTY_OFFSET			8175
#define THIRSTY_COUNTER			11937

#define BYE_OFFSET				11937
#define BYE_COUNTER				14445
 */
/*

#define HII_OFF					0
#define HI_COUN					1544
 */
#define HELLO_OFFSET			0
#define HELLO_COUNTER			4179-1

#define HUNGRY_OFFSET			4179
#define HUNGRY_COUNTER			7105-1

#define HELP_OFFSET				7105
#define HELP_COUNTER			9845-1

#define THIRSTY_OFFSET			9845
#define THIRSTY_COUNTER			12632-1

#define BYE_OFFSET				12632
#define BYE_COUNTER				15651-1

#define WRITE_PORT				PORT_C

/*#define HI_OFFSET				0
#define HI_COUNTER				2605-1

#define HUNGRY_OFFSET			2605
#define HUNGRY_COUNTER			5866-1

#define EX_OFFSET				5866
#define EX_COUNTER				9457-1

#define BYE_OFFSET				9457
#define BYE_COUNTER				11746-1

#define THANK_OFFSET			11746
#define THANK_COUNTER			14505-1

*/
void main(void)
{
	u16 Local_u16Counter=0;
	LED_t Local_LED_tIndicationLed = {LED_PORTB, LED_PIN0, LED_u8ACTIVE_HIGH};

	PORT_voidInit();

	LED_voidLedOn(&Local_LED_tIndicationLed);

	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+HELLO_OFFSET, pgm_read_byte(&hello3_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+HELLO_OFFSET)) == (pgm_read_byte(&hello3_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(HELLO_COUNTER-HELLO_OFFSET))
			break;
	}

	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+HUNGRY_OFFSET, pgm_read_byte(&hungry3_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+HUNGRY_OFFSET)) == (pgm_read_byte(&hungry3_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(HUNGRY_COUNTER-HUNGRY_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+HELP_OFFSET, pgm_read_byte(&help3_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+HELP_OFFSET)) == (pgm_read_byte(&help3_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(HELP_COUNTER-HELP_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+THIRSTY_OFFSET, pgm_read_byte(&thirsty3_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+THIRSTY_OFFSET)) == (pgm_read_byte(&thirsty3_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(THIRSTY_COUNTER-THIRSTY_OFFSET))
			break;
	}
	Local_u16Counter=0;
	while(1)
	{
		PORT_u8ModifyPort(WRITE_PORT, OUTPUT);
		PEEPROM_voidSendDataByte(Local_u16Counter+BYE_OFFSET, pgm_read_byte(&bye3_raw[Local_u16Counter]));
		PORT_u8ModifyPort(WRITE_PORT, INPUT);
		if((PEEPROM_u8ReadDataByte(Local_u16Counter+BYE_OFFSET)) == (pgm_read_byte(&bye3_raw[Local_u16Counter])))
			Local_u16Counter++;
		if(Local_u16Counter==(BYE_COUNTER-BYE_OFFSET))
			break;
	}

	LED_voidLedOff(&Local_LED_tIndicationLed);


}

