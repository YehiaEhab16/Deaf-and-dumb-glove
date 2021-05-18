/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: TIMERS 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMERS_interface.h"
#include "TIMERS_register.h"
#include "TIMERS_config.h"
#include "TIMERS_private.h"

static void (*Timer0_pvOverFlowCallBack)(void) = NULL;
static void (*Timer1_pvOverFlowCallBack)(void) = NULL;
static void (*Timer2_pvOverFlowCallBack)(void) = NULL;

static void (*Timer0_pvCompareMatchCallBack)(void) = NULL;
static void (*Timer1_pvCompareMatchACallBack)(void) = NULL;
static void (*Timer1_pvCompareMatchBCallBack)(void) = NULL;
static void (*Timer2_pvCompareMatchCallBack)(void) = NULL;

static void (*ICU_pvCallBack)(void) = NULL;

void Timer0_voidInit(Timer_t* Copy_pTimer_tStruct)
{
	//check mode
	if(Copy_pTimer_tStruct->Timer_Mode == NORMAL)
	{
		CLR_BIT(TCCR0, TCCR0_WGM01);
		CLR_BIT(TCCR0, TCCR0_WGM00);

		//Set overflow value
		TCNT0 = Copy_pTimer_tStruct->Timer_Value;

		//Set overflow interrupt enable
		SET_BIT(TIMSK, TIMSK_TOIE0);
	}
	
	else if(Copy_pTimer_tStruct->Timer_Mode == CTC)
	{
		SET_BIT(TCCR0, TCCR0_WGM01);
		CLR_BIT(TCCR0, TCCR0_WGM00);

		//Set compare match value
		OCR0 = Copy_pTimer_tStruct->Timer_Value;

		//Set Timer State
		switch(Copy_pTimer_tStruct->Timer_State)
		{
			case TOGGLE_OC:CLR_BIT(TCCR0, TCCR0_COM01);SET_BIT(TCCR0, TCCR0_COM00);break;
			case CLEAR_OC:SET_BIT(TCCR0, TCCR0_COM01);CLR_BIT(TCCR0, TCCR0_COM00);break;
			case SET_OC:SET_BIT(TCCR0, TCCR0_COM01);SET_BIT(TCCR0, TCCR0_COM00);break;
			case NORMAL:
			default:CLR_BIT(TCCR0, TCCR0_COM01);CLR_BIT(TCCR0, TCCR0_COM00);break;
		}

		//Set compare match interrupt enable
		SET_BIT(TIMSK, TIMSK_OCIE0);
	}

	else if(Copy_pTimer_tStruct->Timer_Mode == FAST_PWM)
	{
		SET_BIT(TCCR0, TCCR0_WGM01);
		SET_BIT(TCCR0, TCCR0_WGM00);

		//Set compare match value
		OCR0 = Copy_pTimer_tStruct->Timer_Value;

		//Set PWM State
		switch(Copy_pTimer_tStruct->Timer_State)
		{
			case NORMAL:CLR_BIT(TCCR0, TCCR0_COM01);CLR_BIT(TCCR0, TCCR0_COM00);break;
			case INVERTED:SET_BIT(TCCR0, TCCR0_COM01);SET_BIT(TCCR0, TCCR0_COM00);break;
			case NON_INVERTED:
			default:SET_BIT(TCCR0, TCCR0_COM01);CLR_BIT(TCCR0, TCCR0_COM00);break;
		}
	}

	else if(Copy_pTimer_tStruct->Timer_Mode == PHASE_CORRECT_PWM)
	{
		CLR_BIT(TCCR0, TCCR0_WGM01);
		SET_BIT(TCCR0, TCCR0_WGM00);

		//Set compare match value
		OCR0 = Copy_pTimer_tStruct->Timer_Value;

		//Set PWM State
		switch(Copy_pTimer_tStruct->Timer_State)
		{
			case NORMAL:CLR_BIT(TCCR0, TCCR0_COM01);CLR_BIT(TCCR0, TCCR0_COM00);break;
			case INVERTED:SET_BIT(TCCR0, TCCR0_COM01);SET_BIT(TCCR0, TCCR0_COM00);break;
			case NON_INVERTED:
			default:SET_BIT(TCCR0, TCCR0_COM01);CLR_BIT(TCCR0, TCCR0_COM00);break;
		}
	}

	//Set prescalar
	TCCR0 &= TIMER_u8PRESCALAR_MASK;
	TCCR0 |= Copy_pTimer_tStruct->Timer_Prescalar;
}
void Timer1_voidInit(Timer_t* Copy_pTimer_tStruct)
{
	if(Copy_pTimer_tStruct->Timer_Mode==NORMAL)
	{
		CLR_BIT(TCCR1B, TCCR1B_WGM13);
		CLR_BIT(TCCR1B, TCCR1B_WGM12);
		CLR_BIT(TCCR1A, TCCR1A_WGM11);
		CLR_BIT(TCCR1A, TCCR1A_WGM10);

		//Set overflow value
		TCNT1 = Copy_pTimer_tStruct->Timer_Value;

		//Set overflow interrupt enable
		SET_BIT(TIMSK, TIMSK_TOIE1);
	}

	else if(Copy_pTimer_tStruct->Timer_Mode==CTC)
	{
		CLR_BIT(TCCR1B, TCCR1B_WGM13);
		SET_BIT(TCCR1B, TCCR1B_WGM12);
		CLR_BIT(TCCR1A, TCCR1A_WGM11);
		CLR_BIT(TCCR1A, TCCR1A_WGM10);


		if(Copy_pTimer_tStruct->Timer_Channel==CHANNEL_B)
		{
			//Set compare match value
			OCR1A = Copy_pTimer_tStruct->Timer_Value;

			//Set Timer State
			switch(Copy_pTimer_tStruct->Timer_State)
			{
				case TOGGLE_OC:CLR_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case CLEAR_OC:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case SET_OC:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case NORMAL:
				default:CLR_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);break;
			}

			//Set compare match interrupt enable
			SET_BIT(TIMSK, TIMSK_OCIE1B);
		}

		else
		{
			//Set compare match value
			OCR1A = Copy_pTimer_tStruct->Timer_Value;

			//Set Timer State
			switch(Copy_pTimer_tStruct->Timer_State)
			{
				case TOGGLE_OC:CLR_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case CLEAR_OC:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case SET_OC:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case NORMAL:
				default:CLR_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
			}

			//Set compare match interrupt enable
			SET_BIT(TIMSK, TIMSK_OCIE1A);
		}
	}
	else if(Copy_pTimer_tStruct->Timer_Mode==FAST_PWM)
	{
		SET_BIT(TCCR1B, TCCR1B_WGM13);
		SET_BIT(TCCR1B, TCCR1B_WGM12);
		SET_BIT(TCCR1A, TCCR1A_WGM11);
		CLR_BIT(TCCR1A, TCCR1A_WGM10);

		//Set Top Value
		ICR1 = Copy_pTimer_tStruct->Timer_Top_Value;

		if(Copy_pTimer_tStruct->Timer_Channel==CHANNEL_A)
		{
			//Set compare match value
			OCR1A = Copy_pTimer_tStruct->Timer_Value;

			//Set PWM State
			switch(Copy_pTimer_tStruct->Timer_State)
			{
				case NORMAL:CLR_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case INVERTED:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case NON_INVERTED:
				default:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
			}
		}

		else if(Copy_pTimer_tStruct->Timer_Channel==CHANNEL_B)
		{
			//Set compare match value
			OCR1B = Copy_pTimer_tStruct->Timer_Value;

			//Set PWM State
			switch(Copy_pTimer_tStruct->Timer_State)
			{
				case NORMAL:CLR_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case INVERTED:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case NON_INVERTED:
				default:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);break;
			}
		}
	}

	else if(Copy_pTimer_tStruct->Timer_Mode==PHASE_CORRECT_PWM)
	{
		SET_BIT(TCCR1B, TCCR1B_WGM13);
		CLR_BIT(TCCR1B, TCCR1B_WGM12);
		SET_BIT(TCCR1A, TCCR1A_WGM11);
		CLR_BIT(TCCR1A, TCCR1A_WGM10);

		//Set Top Value
		ICR1 = Copy_pTimer_tStruct->Timer_Top_Value;

		if(Copy_pTimer_tStruct->Timer_Channel==CHANNEL_A)
		{
			//Set PWM State
			switch(Copy_pTimer_tStruct->Timer_State)
			{
				case NORMAL:CLR_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case INVERTED:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
				case NON_INVERTED:
				default:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
			}
		}

		else if(Copy_pTimer_tStruct->Timer_Channel==CHANNEL_B)
		{
			//Set PWM State
			switch(Copy_pTimer_tStruct->Timer_State)
			{
				case NORMAL:CLR_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case INVERTED:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0);break;
				case NON_INVERTED:
				default:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);break;
			}
		}
	}

	//Set prescalar
	TCCR1B &= TIMER_u8PRESCALAR_MASK;
	TCCR1B |= Copy_pTimer_tStruct->Timer_Prescalar;
}
void Timer2_voidInit(Timer_t* Copy_pTimer_tStruct)
{
	//check mode
	if(Copy_pTimer_tStruct->Timer_Mode == NORMAL)
	{
		CLR_BIT(TCCR2, TCCR2_WGM21);
		CLR_BIT(TCCR2, TCCR2_WGM20);

		//Set overflow value
		TCNT2 = Copy_pTimer_tStruct->Timer_Value;

		//Set overflow interrupt enable
		SET_BIT(TIMSK, TIMSK_TOIE2);
	}

	else if(Copy_pTimer_tStruct->Timer_Mode == CTC)
	{
		SET_BIT(TCCR2, TCCR2_WGM21);
		CLR_BIT(TCCR2, TCCR2_WGM20);

		//Set compare match value
		OCR2 = Copy_pTimer_tStruct->Timer_Value;

		//Set Timer State
		switch(Copy_pTimer_tStruct->Timer_State)
		{
			case TOGGLE_OC:CLR_BIT(TCCR2, TCCR2_COM21);SET_BIT(TCCR2, TCCR2_COM20);break;
			case CLEAR_OC:SET_BIT(TCCR2, TCCR2_COM21);CLR_BIT(TCCR2, TCCR2_COM20);break;
			case SET_OC:SET_BIT(TCCR2, TCCR2_COM21);SET_BIT(TCCR2, TCCR2_COM20);break;
			case NORMAL:
			default:CLR_BIT(TCCR2, TCCR2_COM21);CLR_BIT(TCCR2, TCCR2_COM20);break;
		}

		//Set compare match interrupt enable
		SET_BIT(TIMSK, TIMSK_OCIE2);
	}

	else if(Copy_pTimer_tStruct->Timer_Mode == FAST_PWM)
	{
		SET_BIT(TCCR2, TCCR2_WGM21);
		SET_BIT(TCCR2, TCCR2_WGM20);

		//Set compare match value
		OCR2 = Copy_pTimer_tStruct->Timer_Value;

		//Set PWM State
		switch(Copy_pTimer_tStruct->Timer_State)
		{
			case NORMAL:CLR_BIT(TCCR2, TCCR2_COM21);CLR_BIT(TCCR2, TCCR2_COM20);break;
			case INVERTED:SET_BIT(TCCR2, TCCR2_COM21);SET_BIT(TCCR2, TCCR2_COM20);break;
			case NON_INVERTED:
			default:SET_BIT(TCCR2, TCCR2_COM21);CLR_BIT(TCCR2, TCCR2_COM20);break;
		}
	}

	else if(Copy_pTimer_tStruct->Timer_Mode == PHASE_CORRECT_PWM)
	{
		CLR_BIT(TCCR2, TCCR2_WGM21);
		SET_BIT(TCCR2, TCCR2_WGM20);

		//Set compare match value
		OCR0 = Copy_pTimer_tStruct->Timer_Value;

		//Set PWM State
		switch(Copy_pTimer_tStruct->Timer_State)
		{
			case NORMAL:CLR_BIT(TCCR2, TCCR2_COM21);CLR_BIT(TCCR2, TCCR2_COM20);break;
			case INVERTED:SET_BIT(TCCR2, TCCR2_COM21);SET_BIT(TCCR2, TCCR2_COM20);break;
			case NON_INVERTED:
			default:SET_BIT(TCCR2, TCCR2_COM21);CLR_BIT(TCCR2, TCCR2_COM20);break;
		}
	}

	//Set prescalar
	TCCR2 &= TIMER_u8PRESCALAR_MASK;
	TCCR2 |= Copy_pTimer_tStruct->Timer_Prescalar;
}

void ICU_voidInit(void)
{
	//Set trigger to rising edge
	SET_BIT(TCCR1B, TCCR1B_ICES1);

	//Set Input capture interrupt enable
	SET_BIT(TIMSK, TIMSK_TICIE1);
}

u8 Timer_u8SetCallback(u8 Copy_u8TimerId, void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	
	if(Copy_pvCallBackFunc!=NULL)
	{
		switch(Copy_u8TimerId)
		{
		case TIMER0_PRELOAD:Timer0_pvOverFlowCallBack=Copy_pvCallBackFunc;break;
		case TIMER1_PRELOAD:Timer1_pvOverFlowCallBack=Copy_pvCallBackFunc;break;
		case TIMER2_PRELOAD:Timer2_pvOverFlowCallBack=Copy_pvCallBackFunc;break;

		case TIMER0_COMPARE_MATCH:  Timer0_pvCompareMatchCallBack=Copy_pvCallBackFunc;break;
		case TIMER1_COMPARE_MATCH_A:Timer1_pvCompareMatchACallBack=Copy_pvCallBackFunc;break;
		case TIMER1_COMPARE_MATCH_B:Timer1_pvCompareMatchBCallBack=Copy_pvCallBackFunc;break;
		case TIMER2_COMPARE_MATCH:  Timer2_pvCompareMatchCallBack=Copy_pvCallBackFunc;break;

		case ICU:ICU_pvCallBack=Copy_pvCallBackFunc;break;
		}
	}

	else
		Local_u8ErrorState=NULL_POINTER;

	return Local_u8ErrorState;
}

void Timer_voidSetTimerValue(u8 Copy_u8TimerId, u16 Copy_u16Value)
{
	switch(Copy_u8TimerId)
	{
		case TIMER0_PRELOAD: TCNT0=Copy_u16Value;break;
		case TIMER1_PRELOAD: TCNT1=Copy_u16Value;break;
		case TIMER2_PRELOAD: TCNT2=Copy_u16Value;break;

		case TIMER0_COMPARE_MATCH: OCR0=Copy_u16Value;break;
		case TIMER1_COMPARE_MATCH_A: OCR1A=Copy_u16Value;break;
		case TIMER1_COMPARE_MATCH_B: OCR1B=Copy_u16Value;break;
		case TIMER2_COMPARE_MATCH: OCR2=Copy_u16Value;break;
	}
}
u16 Timer_u16ReadTimerValue(u8 Copy_u8TimerId)
{
	switch(Copy_u8TimerId)
	{
		case TIMER0: return TCNT0;
		case TIMER1: return TCNT1;
		case TIMER2: return TCNT2;
		case ICU:    return ICR1;
		default: return 0;
	}
}

u8 ICU_u8SetTrigger(u8 Copu_u8Trigger)
{
	u8 Local_u8ErrorState=OK;

	switch(Copu_u8Trigger)
	{
		case FALLING_EDGE:CLR_BIT(TCCR1B, TCCR1B_ICES1);break;
		case RISING_EDGE: SET_BIT(TCCR1B, TCCR1B_ICES1);break;
		default:Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}
void ICU_voidDisbleInterrupt(void)
{
	CLR_BIT(TIMSK, TIMSK_TICIE1);
}

void Timer_voidDisableInterrupt(u8 Copy_u8TimerID)
{
	if(Copy_u8TimerID==TIMER0_COMPARE_MATCH)
		CLR_BIT(TIMSK, TIMSK_OCIE0);
}

void PWM_voidInit(PWM_t* Copy_pPWM_tStruct)
{
	Timer_t Local_Timer_tPWM = {FAST_PWM, DIVIDE_BY_8, Copy_pPWM_tStruct->PWM_Value, NON_INVERTED};
	if(Copy_pPWM_tStruct->Channel_Id==TIMER0)
		Timer0_voidInit(&Local_Timer_tPWM);
	else if(Copy_pPWM_tStruct->Channel_Id==TIMER2)
		Timer2_voidInit(&Local_Timer_tPWM);
	else if(Copy_pPWM_tStruct->Channel_Id==TIMER1_CHANNEL_A)
	{
		Local_Timer_tPWM.Timer_Channel=CHANNEL_A;
		Local_Timer_tPWM.Timer_Top_Value=MAX;

		Timer1_voidInit(&Local_Timer_tPWM);
	}
	else if(Copy_pPWM_tStruct->Channel_Id==TIMER1_CHANNEL_B)
	{
		Local_Timer_tPWM.Timer_Channel=CHANNEL_B;
		Local_Timer_tPWM.Timer_Top_Value=MAX;

		Timer1_voidInit(&Local_Timer_tPWM);
	}
}
void PWM_voidAnalogWrite(PWM_t* Copy_pPWM_tStruct)
{
	if(Copy_pPWM_tStruct->Channel_Id==TIMER0)
		Timer_voidSetTimerValue(TIMER0_COMPARE_MATCH, Copy_pPWM_tStruct->PWM_Value);
	else if(Copy_pPWM_tStruct->Channel_Id==TIMER2)
		Timer_voidSetTimerValue(TIMER2_COMPARE_MATCH, Copy_pPWM_tStruct->PWM_Value);
	else if(Copy_pPWM_tStruct->Channel_Id==TIMER1_CHANNEL_A)
		Timer_voidSetTimerValue(TIMER1_COMPARE_MATCH_A, Copy_pPWM_tStruct->PWM_Value);
	else if(Copy_pPWM_tStruct->Channel_Id==TIMER1_CHANNEL_B)
		Timer_voidSetTimerValue(TIMER1_COMPARE_MATCH_B, Copy_pPWM_tStruct->PWM_Value);
}

u16 mapping(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum)
{
	u16 Local_u16OutputNumber = (u16)(((f32)(Copy_u16OutputMaximum - Copy_u16OutputMinimum) / (f32)(Copy_u16InputMaximum - Copy_u16InputMinimum))*(f32)(Copy_u16InputNumber - Copy_u16InputMinimum)) + Copy_u16OutputMinimum;

	return Local_u16OutputNumber;
}

//Timer/Counter2 Compare Match ISR
void __vector_4 (void)		__attribute__((signal));
void __vector_4 (void)
{
	if(Timer2_pvCompareMatchCallBack!=NULL)
		Timer2_pvCompareMatchCallBack();
}

//Timer/Counter2 Overflow ISR
void __vector_5 (void)		__attribute__((signal));
void __vector_5 (void)
{
	if(Timer2_pvOverFlowCallBack!=NULL)
		Timer2_pvOverFlowCallBack();
}

//Timer/Counter1 Capture Event ISR
void __vector_6 (void)		__attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pvCallBack!=NULL)
		ICU_pvCallBack();
}

//Timer/Counter1 Compare Match A ISR
void __vector_7 (void)		__attribute__((signal));
void __vector_7 (void)
{
	if(Timer1_pvCompareMatchACallBack!=NULL)
		Timer1_pvCompareMatchACallBack();
}

//Timer/Counter1 Compare Match B ISR
void __vector_8 (void)		__attribute__((signal));
void __vector_8 (void)
{
	if(Timer1_pvCompareMatchBCallBack!=NULL)
		Timer1_pvCompareMatchBCallBack();
}

//Timer/Counter1 Overflow ISR
void __vector_9 (void)		__attribute__((signal));
void __vector_9 (void)
{
	if(Timer1_pvOverFlowCallBack!=NULL)
		Timer1_pvOverFlowCallBack();
}

//Timer/Counter0 Compare Match ISR
void __vector_10 (void)		__attribute__((signal));
void __vector_10 (void)
{
	if(Timer0_pvCompareMatchCallBack!=NULL)
		Timer0_pvCompareMatchCallBack();
}

//Timer/Counter0 Overflow ISR
void __vector_11 (void)		__attribute__((signal));
void __vector_11 (void)
{
	if(Timer0_pvOverFlowCallBack!=NULL)
		Timer0_pvOverFlowCallBack();
}
