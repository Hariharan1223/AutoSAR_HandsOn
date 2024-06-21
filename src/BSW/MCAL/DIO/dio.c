
#include<dio.h>

/* DIO pin Read and Write functionality */
unsigned int readval;
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	
	if( ChannelId == GPIO_PORTA_PIN_3)
	{
		ReadVal = GPIOA_IDR & (1 << 3); // Assuming GPIOA->IDR holds the port input data register
		 if (readval == 0x00) /* If pin is LOW */
		
        return STD_LOW;
    
    else
                       
        return STD_HIGH; /* If pin is high */
  
	}
	else
	{
    /* Log an error if an invalid channel is requested */
    Dio_ReportError(DIO_E_PARAM_INVALID_CHANNEL_ID);
    return STD_LOW; // or any appropriate default value
	}
		
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
		if (ChannelId == GPIO_PORTA_PIN_3)
		{
			if (Level == STD_LOW)
				GPIOA_ODR &= ~(1 << 3); / Code to set pin LOW /

			else
				GPIOA_ODR |= (1 << 3); / Code to set pin high /

		}
			else
			{
				/ Log an error if an invalid channel is requested */
				Dio_ReportError(DIO_E_PARAM_INVALID_CHANNEL_ID);
			}
}
	