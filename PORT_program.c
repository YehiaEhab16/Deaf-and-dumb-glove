/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: PORT 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-8-2018 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_register.h"
#include "PORT_interface.h"


void PORT_voidInit(void)
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	
	PORTA = PORTA_INITIAL_VALUE;
	PORTB = PORTB_INITIAL_VALUE;
	PORTC = PORTC_INITIAL_VALUE;
	PORTD = PORTD_INITIAL_VALUE;
}

u8 PORT_u8ModifyPort(u8 Copy_u8Port, u8 Copy_u8State)
{
	u8 Local_ErrorState=OK;
	
	switch(Copy_u8Port)
	{
		case PORT_A: DDRA = (Copy_u8State ? 0xff:0x00);break;
		case PORT_B: DDRB = (Copy_u8State ? 0xff:0x00);break;
		case PORT_C: DDRC = (Copy_u8State ? 0xff:0x00);break;
		case PORT_D: DDRD = (Copy_u8State ? 0xff:0x00);break;
		default: Local_ErrorState=NOK;
	}
	
	return Local_ErrorState;
}
u8 PORT_u8ModifyPin(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8State)
{
	u8 Local_ErrorState=OK;
	
	switch(Copy_u8Port)
	{
		case PORT_A: Copy_u8State ? (SET_BIT(DDRA,Copy_u8Pin)):(CLR_BIT(DDRA,Copy_u8Pin));break;
		case PORT_B: Copy_u8State ? (SET_BIT(DDRB,Copy_u8Pin)):(CLR_BIT(DDRB,Copy_u8Pin));break;
		case PORT_C: Copy_u8State ? (SET_BIT(DDRC,Copy_u8Pin)):(CLR_BIT(DDRC,Copy_u8Pin));break;
		case PORT_D: Copy_u8State ? (SET_BIT(DDRD,Copy_u8Pin)):(CLR_BIT(DDRD,Copy_u8Pin));break;
		default: Local_ErrorState=NOK;
	}
	
	return Local_ErrorState;
}
