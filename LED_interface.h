/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: LED				************/
/************		Version: 1.00	 		************/
/************		Date: 1-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define LED_u8ACTIVE_HIGH		1
#define LED_u8ACTIVE_LOW 		0

#define LED_PORTA				DIO_u8PORTA
#define LED_PORTB				DIO_u8PORTB
#define LED_PORTC				DIO_u8PORTC
#define LED_PORTD				DIO_u8PORTD

#define LED_PIN0					DIO_u8PIN0
#define LED_PIN1					DIO_u8PIN1
#define LED_PIN2					DIO_u8PIN2
#define LED_PIN3					DIO_u8PIN3
#define LED_PIN4					DIO_u8PIN4
#define LED_PIN5					DIO_u8PIN5
#define LED_PIN6					DIO_u8PIN6
#define LED_PIN7					DIO_u8PIN7

typedef struct My_Struct1
{
	u8 LED_u8Port;
	u8 LED_u8Pin;
	u8 LED_u8Connection;
}LED_t;

void LED_voidLedOn(LED_t* Copy_pu8StructLed);
void LED_voidLedOff(LED_t* Copy_pu8StructLed);
void LED_voidLedPortValue(LED_t* Copy_pu8StructLed, u8 Copy_u8Value);
void LED_voidLedToggle(LED_t* Copy_pu8StructLed);


#endif
