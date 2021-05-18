/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: GIE 				************/
/************		Version: 1.00	 		************/
/************		Date: 14-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_register.h"
#include "GIE_interface.h"

void GIE_voidEnableGlobal(void)
{
	SET_BIT(SREG, SREG_I);
}

void GIE_voidDisableGlobal(void)
{
	CLR_BIT(SREG, SREG_I);
}

