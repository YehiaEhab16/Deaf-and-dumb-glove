/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: TIMERS 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

#define FALLING_EDGE			1
#define RISING_EDGE				2

#define NORMAL					1
#define CTC						2
#define PHASE_CORRECT_PWM		3
#define FAST_PWM				4

#define TIMER0					1
#define TIMER1					2
#define TIMER1_CHANNEL_A		9
#define TIMER1_CHANNEL_B		10
#define TIMER2					3
#define ICU						8

#define TIMER0_PRELOAD			1
#define TIMER1_PRELOAD			2
#define TIMER2_PRELOAD			3
#define TIMER0_COMPARE_MATCH		4
#define TIMER1_COMPARE_MATCH_A		5
#define TIMER1_COMPARE_MATCH_B		6
#define TIMER2_COMPARE_MATCH		7

#define STOP					0
#define DIVIDE_BY_1				1
#define DIVIDE_BY_8				2
#define DIVIDE_BY_64			3
#define DIVIDE_BY_256			4
#define DIVIDE_BY_1024			5
#define EXT_FALLING_EDGE		6
#define EXT_RISING_EDGE			7

#define TOGGLE_OC				2
#define CLEAR_OC				3
#define SET_OC					4

#define NON_INVERTED			2
#define INVERTED				3

#define CHANNEL_A				1
#define CHANNEL_B				2

#define MAX						255
#define MAX2					205

typedef struct My_Struct77
{
	u8 Timer_Mode;
	u8 Timer_Prescalar;
	u16 Timer_Value;
	u8 Timer_State;			//In case of Compare match and PWM
	u8 Timer_Channel;		//In case of Timer 1 Compare match and PWM
	u16 Timer_Top_Value;		//In case of Timer 1 PWM
}Timer_t;

typedef struct My_Struct76
{
	u8 Channel_Id;
	u8 PWM_Value;
}PWM_t;

void Timer0_voidInit(Timer_t* Copy_pTimer_tStruct);
void Timer1_voidInit(Timer_t* Copy_pTimer_tStruct);
void Timer2_voidInit(Timer_t* Copy_pTimer_tStruct);

void ICU_voidInit(void);

u8 Timer_u8SetCallback(u8 Copy_u8TimerId, void (*Copy_pvCallBackFunc)(void));

void Timer_voidSetTimerValue(u8 Copy_u8TimerId, u16 Copy_u16Value);
u16 Timer_u16ReadTimerValue(u8 Copy_u8TimerId);

u8 ICU_u8SetTrigger(u8 Copu_u8Trigger);
void ICU_voidDisbleInterrupt(void);
void Timer_voidDisableInterrupt(u8 Copy_u8TimerID);

void PWM_voidInit(PWM_t* Copy_pPWM_tStruct);
void PWM_voidAnalogWrite(PWM_t* Copy_pPWM_tStruct);

u16 mapping(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum);


#endif
