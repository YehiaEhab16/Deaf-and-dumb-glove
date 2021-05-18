/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: ADC 				************/
/************		Version: 1.00	 		************/
/************		Date: 17-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct My_Strcut21
{
	u8* Channel;
	u8 ChainSize;
	u16* Result;
	void (*NotificationFunc)(void);
}Chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Result);

u8 ADC_u8StartChainConversionSynch(Chain_t* Copy_Chain);

//Must Enable Global Interrupt
u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void));

//Must Enable Global Interrupt
u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_Chain);


#endif
