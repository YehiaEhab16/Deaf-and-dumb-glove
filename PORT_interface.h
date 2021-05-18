/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: PORT 				************/
/************		Version: 1.10	 		************/
/************		Date: 6-1-2021			************/
/*******************************************************/
/*******************************************************/

#define INPUT		0
#define OUTPUT		1

#define ALL			2
#define NONE		3

#define PORT_A		0
#define	PORT_B		1
#define	PORT_C		2
#define PORT_D		3

#define	PIN0		0
#define	PIN1		1
#define	PIN2		2
#define	PIN3		3
#define	PIN4		4
#define	PIN5		5
#define	PIN6		6
#define	PIN7		7

/* Preprocessor file guard */
#ifndef PORT_INTERFACE_H_
#define PORT_INTERFACE_H_

void PORT_voidInit(void); 

u8 PORT_u8ModifyPort(u8 Copy_u8Port, u8 Copy_u8State);
u8 PORT_u8ModifyPin(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8State);


#endif
