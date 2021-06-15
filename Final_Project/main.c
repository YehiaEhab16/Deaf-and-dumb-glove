/* main.c
 *
 *  Created on: Jan 27, 2021
 *      Author: yehia
 */

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "TIMERS_interface.h"

#include "LED_interface.h"
#include "PEEPROM_interface.h"

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

void Timer_ISR(void);

u8 Global_u8Flag=0;
u16 Global_u16Counter, Global_u16Offset;

LED_t Global_Ind1 = {LED_PORTA, LED_PIN5, LED_u8ACTIVE_HIGH};
LED_t Global_Ind2 = {LED_PORTA, LED_PIN6, LED_u8ACTIVE_HIGH};

void main(void)
{
	u16 Local_u16Sensor1, Local_u16Sensor2, Local_u16Sensor3, Local_u16Sensor4, Local_u16Sensor5;
	Timer_t Local_Timer_tOne = {CTC, DIVIDE_BY_1, 2500, NORMAL};

	PORT_voidInit();
	ADC_voidInit();

	Timer1_voidInit(&Local_Timer_tOne);
	Timer_u8SetCallback(TIMER1_COMPARE_MATCH_A, &Timer_ISR);

	GIE_voidEnableGlobal();

	while(1)
	{
		ADC_u8StartConversionSynch(0, &Local_u16Sensor1);
		ADC_u8StartConversionSynch(1, &Local_u16Sensor2);
		ADC_u8StartConversionSynch(2, &Local_u16Sensor3);
		ADC_u8StartConversionSynch(3, &Local_u16Sensor4);
		ADC_u8StartConversionSynch(4, &Local_u16Sensor5);

		if(Local_u16Sensor1<200)
		{
			Global_u8Flag=1;
			Global_u16Counter=HELP_COUNTER;
			Global_u16Offset= HELP_OFFSET;
		}
		else if(Local_u16Sensor2<200)
		{
			Global_u8Flag=1;
			Global_u16Counter=HUNGRY_COUNTER;
			Global_u16Offset=HUNGRY_OFFSET;
		}

		else if(Local_u16Sensor3<200)
		{
			Global_u8Flag=1;
			Global_u16Counter=THIRSTY_COUNTER;
			Global_u16Offset=THIRSTY_OFFSET;
		}

		else if(Local_u16Sensor4<200)
		{
			Global_u8Flag=1;
			Global_u16Counter=HELLO_COUNTER;
			Global_u16Offset=HELLO_OFFSET;
		}

		else if(Local_u16Sensor5<200)
		{
			Global_u8Flag=1;
			Global_u16Counter=BYE_COUNTER;
			Global_u16Offset=BYE_OFFSET;
		}


	}

}

void Timer_ISR(void)
{
	static u16 Local_u16Counter=0;

	if(Global_u8Flag==1)
	{
		PEEPROM_u8ReadDataByte(Local_u16Counter+Global_u16Offset);
		if((Local_u16Counter+Global_u16Offset)==Global_u16Counter)
		{
			Local_u16Counter=0;
			Global_u8Flag=0;
			LED_voidLedToggle(&Global_Ind1);
		}
		Local_u16Counter++;
	}

	else
		PPEPROM_voidDisableOutput();
}

