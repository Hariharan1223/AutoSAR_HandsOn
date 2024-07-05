/**
 * @file adc.c
 * @brief adc driver implementation
 */
#include "adc.h"

Std_ReturnType Adc_Init(void)
{
	/* Enable the ADC peripheral */
	ADC_CR |= ADC_CR_ADEN;
	
	if(ADC_CR != 0)
		return ADC_E_OK;
	else
		return ADC_E_NOT_OK;
}

void Adc_StartGroupConversion(Adc_GroupType Group)
{
	if (Group == ADC_GROUP_SPEED_SENSOR)
		{
		/* Set the sampling time for the speed sensor channel */
		ADC_SMPR |= (ADC_SMPR_SMP_VAL << (ADC_CHANNEL_5 * 3));

		/* Start the ADC conversion for the speed sensor channel */
		ADC_CR |= (ADC_CR_ADSTART | (1 << ADC_CHANNEL_5));
	}
	else
	{
		/* Log an error if an invalid group is requested */
		Adc_ReportError(ADC_E_PARAM_GROUP);
	}
}

Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr)
{
	if (DataBufferPtr == NULL)
	{
		/* Log an error if the data buffer pointer is NULL */
		Adc_ReportError(ADC_E_NULL_POINTER);
		return ADC_E_NULL_POINTER;
	}

	if (Group == ADC_GROUP_SPEED_SENSOR)
	{
		/* Check if the ADC conversion is complete */
		if ((ADC_SR & ADC_SR_EOC) != 0)
		{
		/* Read the ADC value from the data register */
			*DataBufferPtr = ADC_DR;
			return ADC_E_OK;
		}
		else
		{
			/* Log an error if the conversion is not complete */
			Adc_ReportError(ADC_E_CONV_NOT_COMPLETED);
			return ADC_E_CONV_NOT_COMPLETED;
		}
    }
	
	else
	{
		/* Log an error if an invalid group is requested */
		Adc_ReportError(ADC_E_PARAM_GROUP);
		return ADC_E_PARAM_GROUP;
	}
}

/* Adc_GetGroupStatus function to check ADC status*/
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group)
{
	if (Group == ADC_GROUP_SPEED_SENSOR)
	{
		if (ADC_SR & ADC_SR_EOC)
			return ADC_COMPLETED;
		else if (ADC_CR & ADC_CR_ADSTART)
			return ADC_BUSY;
		else
			return ADC_IDLE;
	}
	else
	{
		Adc_ReportError(ADC_E_PARAM_GROUP);
		return ADC_IDLE;
	}
}
