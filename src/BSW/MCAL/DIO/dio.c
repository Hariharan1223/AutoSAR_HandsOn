/**
 * @file dio.c
 * @brief dio driver implementation
 */

#include<dio.h>
#include "Std_Types.h"
/* DIO pin Read and Write functionality */
unsigned int readval;

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	if( ChannelId == GPIO_PORTA_PIN_3)
	{
		/* Assuming GPIOA->IDR holds the port input data register*/
		readval = GPIOA_IDR & (1 << 3); 
		/* If pin is LOW */
		if (readval == 0x00) 
			return STD_LOW;    
		else
		/* If pin is high */               
			return STD_HIGH;
 
	}
	else
	{
		Dio_ReportError(DIO_E_PARAM_INVALID_CHANNEL_ID);
		return STD_LOW;
	}
		
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	if (ChannelId == GPIO_PORTA_PIN_3)
		{
			if (Level == STD_LOW)
				/* Code to set pin LOW */
				GPIOA_ODR &= ~(1 << 3);  
			else
				/* Code to set pin high */
				GPIOA_ODR |= (1 << 3);  
		}
	else	
		Dio_ReportError(DIO_E_PARAM_INVALID_CHANNEL_ID);
		
}
	