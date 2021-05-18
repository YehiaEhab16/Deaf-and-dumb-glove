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
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define DIVISION_BY_2			1
#define DIVISION_BY_4			2
#define DIVISION_BY_8			3
#define DIVISION_BY_16			4
#define DIVISION_BY_32			5
#define DIVISION_BY_64			6
#define DIVISION_BY_128			7

#define ADC_u8CHANNEL_MASK		0b11100000
#define ADC_u8PRESCALAR_MASK	0b11111000

#define SINGLE_CONVERSION		0
#define CHAIN_CONVERSION		1

#define IDLE					0
#define BUSY					1

#define AREF					1
#define AVCC					2
#define REF2V56					3

#define ADC_BITS_8				1
#define ADC_BITS_10				2

#define ENABLED					1
#define DISABLED				2



#endif
