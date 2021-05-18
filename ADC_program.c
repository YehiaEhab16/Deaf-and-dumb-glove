/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: ADC 				************/
/************		Version: 1.00	 		************/
/************		Date: 17-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

//Global pointer to carry conversion result (asynch)
static u16* ADC_pu16ConversionResult = NULL;

//Global function
static void (*ADC_pvNotificationFunc)(void) = NULL;

static u8 ADC_u8ChainSize;

static u8 ADC_u8ChainIndex;

static u8* ADC_pu8ChainChannel=NULL;

static u8 ADC_u8State = IDLE;

static u8 ADC_u8ISRSource;

void ADC_voidInit(void)
{
	//Select AVCC reference voltage
	#if ADC_REFERENCE == AVCC
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	#elif ADC_REFERENCE == AREF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	#elif ADC_REFERENCE == REF2V56
	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);

	#else
	#error "Not a valid reference voltage"

 	 #endif

	//Activate left adjust for 8-bit resolution
	#if ADC_RESOLUTION == ADC_BITS_8
	SET_BIT(ADMUX, ADMUX_ADLAR);

	#elif ADC_RESOLUTION == ADC_BITS_10
	CLR_BIT(ADMUX, ADMUX_ADLAR);

	#else
	#error "Not a valid resolution"

	#endif

	ADCSRA &= ADC_u8PRESCALAR_MASK;  //Clear first 3 bits in ADCSRA register
	ADCSRA |= ADC_u8PRESCALAR; //Set the required configuration

	//Enable ADC peripheral
	#if ADC_STATE == ENABLED
	SET_BIT(ADCSRA, ADCSRA_ADEN);

	#elif ADC_STATE == DISABLED
	CLR_BIT(ADCSRA, ADCSRA_ADEN);

	#else
	#error "Not a valid state"

	#endif
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Result)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u32Counter=0;

	if(Copy_pu16Result != NULL)
	{
		if(ADC_u8State==IDLE)
		{
			ADC_u8State = BUSY;
			//Clear first 3 bits in ADMUX register
			ADMUX &= ADC_u8CHANNEL_MASK;
			ADMUX |= Copy_u8Channel; //Set the required channel

			//Start Conversion
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			//Busy waiting (polling) until the conversion is complete
			while(((GET_BIT(ADCSRA, ADCSRA_ADIF))==0) && (Local_u32Counter<ADC_u32Timeout))
			{
				Local_u32Counter++;
			}

			if(Local_u32Counter==ADC_u32Timeout)
				Local_u8ErrorState = TIMEOUT_STATE;

			else
			{
			//Clear the interrupt flag
			SET_BIT(ADCSRA, ADCSRA_ADIF);

			#if ADC_RESOLUTION == ADC_BITS_8
			*Copy_pu16Result = ADCH;

			#elif ADC_RESOLUTION == ADC_BITS_10
			*Copy_pu16Result = (ADCL | (ADCH<<8));

			#endif
			}
			ADC_u8State = IDLE;
		}
		else
			Local_u8ErrorState = BUSY_STATE;
	}
		else
			Local_u8ErrorState = NULL_POINTER;

	return Local_u8ErrorState;
}

u8 ADC_u8StartChainConversionSynch(Chain_t* Copy_Chain)
{
	u8 Local_u8ErrorState=OK, Local_u8ChainIndex;
	u32 Local_u32Counter=0;
	
	if((Copy_Chain!=NULL && Copy_Chain->Channel!=NULL) && (Copy_Chain->Result!=NULL))
	{
		if(ADC_u8State==IDLE)
		{
			ADC_u8State=BUSY;
			for(Local_u8ChainIndex=0;Local_u8ChainIndex<Copy_Chain->ChainSize;Local_u8ChainIndex++)
			{
				//Clear first 3 bits in ADMUX register
				ADMUX &= ADC_u8CHANNEL_MASK;
				ADMUX |= Copy_Chain->Channel[Local_u8ChainIndex]; //Set the required channel

				//Start Conversion
				SET_BIT(ADCSRA, ADCSRA_ADSC);

				while(((GET_BIT(ADCSRA, ADCSRA_ADIF))==0) && (Local_u32Counter<ADC_u32Timeout))
				{
					Local_u32Counter++;
				}

				if(Local_u32Counter==ADC_u32Timeout)
				{
					Local_u8ErrorState = TIMEOUT_STATE;
					break;
				}

				else
				{
				//Clear the interrupt flag
				SET_BIT(ADCSRA, ADCSRA_ADIF);

				#if ADC_RESOLUTION == ADC_BITS_8
				Copy_Chain->Result[Local_u8ChainIndex] = ADCH;

				#elif ADC_RESOLUTION == ADC_BITS_10
				Copy_Chain->Result[Local_u8ChainIndex] = (ADCL | (ADCH<<8));

				#endif
				}
				ADC_u8State = IDLE;
			}
		}
		else
			Local_u8ErrorState=BUSY_STATE;
	}
	else
		Local_u8ErrorState=NULL_POINTER;

	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;

	if((Copy_pu16Result!=NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if(ADC_u8State==IDLE)
		{
			//ADC is now Busy
			ADC_u8State = BUSY;

			ADC_u8ISRSource = SINGLE_CONVERSION;

			ADC_pu16ConversionResult = Copy_pu16Result;

			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			//Clear first 3 bits in ADMUX register
			ADMUX &= ADC_u8CHANNEL_MASK;
			ADMUX |= Copy_u8Channel; //Set the required channel

			//Start Conversion
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			//set interrupt enable
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
		else
			Local_u8ErrorState = BUSY_STATE;
	}

	else
		Local_u8ErrorState=NULL_POINTER;

	return Local_u8ErrorState;
}

u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_Chain)
{
	u8 Local_u8ErrorState=OK;

	if((Copy_Chain!=NULL && Copy_Chain->Channel!=NULL) && (Copy_Chain->NotificationFunc!=NULL) && (Copy_Chain->Result!=NULL))
	{
		if(ADC_u8State==IDLE)
		{
			ADC_u8State=BUSY;

			ADC_u8ISRSource = CHAIN_CONVERSION;

			ADC_pu16ConversionResult = Copy_Chain->Result;
			ADC_pu8ChainChannel = Copy_Chain->Channel;
			ADC_pvNotificationFunc = Copy_Chain->NotificationFunc;
			ADC_u8ChainSize = Copy_Chain->ChainSize;

			ADC_u8ChainIndex=0;

			//Clear first 3 bits in ADMUX register
			ADMUX &= ADC_u8CHANNEL_MASK;
			ADMUX |= ADC_pu8ChainChannel[ADC_u8ChainIndex]; //Set the required channel

			//Start Conversion
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			//set interrupt enable
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
		else
			Local_u8ErrorState=BUSY_STATE;
	}
	else
		Local_u8ErrorState=NULL_POINTER;

	return Local_u8ErrorState;
}

void __vector_16 (void)		__attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource == SINGLE_CONVERSION)
	{
		//Read Result
		#if ADC_RESOLUTION == ADC_BITS_8
		*ADC_pu16ConversionResult = ADCH;

		#elif ADC_RESOLUTION == ADC_BITS_10
		*ADC_pu16ConversionResult = (ADCL | (ADCH<<8));

		#endif

		//ADC is now IDLE
		ADC_u8State = IDLE;

		//Invoke Callback Function
		ADC_pvNotificationFunc();

		//disable interrupt enable
		CLR_BIT(ADCSRA, ADCSRA_ADIE);
	}
	else
	{
		//Read Result
		#if ADC_RESOLUTION == ADC_BITS_8
		ADC_pu16ConversionResult[ADC_u8ChainIndex] = ADCH;

		#elif ADC_RESOLUTION == ADC_BITS_10
		ADC_pu16ConversionResult[ADC_u8ChainIndex] = (ADCL | (ADCH<<8));

		#endif

		//Increment Index
		ADC_u8ChainIndex++;

		if(ADC_u8ChainIndex==ADC_u8ChainSize)
		{
			//Conversion Finished
			ADC_u8State = IDLE;

			//Disable Interrupt
			CLR_BIT(ADCSRA, ADCSRA_ADIE);

			//Invoke Call Back
			ADC_pvNotificationFunc();
		}
		else
		{
			//Conversion Not Finished
			//Clear first 3 bits in ADMUX register
			ADMUX &= ADC_u8CHANNEL_MASK;
			ADMUX |= ADC_pu8ChainChannel[ADC_u8ChainIndex]; //Set the required channel

			//Start Conversion
			SET_BIT(ADCSRA, ADCSRA_ADSC);

		}
	}
}
