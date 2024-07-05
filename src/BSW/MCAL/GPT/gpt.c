/**
 * @file gpt.c
 * @brief gpt driver implementation
 */
 
#include "Gpt.h"

#define GPT_MAX_CHANNELS 1  // We only need one channel for speed monitoring
static Gpt_CallbackType Gpt_Callbacks[GPT_MAX_CHANNELS];

void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
	if (ConfigPtr == NULL)
    {
		/* Report an error for null pointer */
		gpt_ReportError(GPT_E_PARAM_NULL_PTR);
		return;
	}
	/* Enable GPT */
	GPT_CR1 |= GPT_CR1_EN;

	/* Set the period */
	GPT_ARR = ConfigPtr->Period;
	
	/* Enable interrupt */
	GPT_DIER |= GPT_DIER_UIE;
}

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
	/* Check if the channel is valid */
	if (Channel < GPT_MAX_CHANNELS)
	{
		/* Set the value to start the timer */
		GPT_CNT = Value;
		/* Start the timer */
		GPT_CR1 |= GPT_CR1_CEN;
	}
	else
	{
		/* Report an error if an invalid channel is requested */
		gpt_ReportError(GPT_E_PARAM_INVALID_CHANNEL);
	}
}

void Gpt_StopTimer(Gpt_ChannelType Channel)
{
	/* Check if the channel is valid */
	if (Channel < GPT_MAX_CHANNELS)
	{
		/* Stop the timer by resetting the counter register */
		GPT_CR1 &= ~GPT_CR1_CEN;
		GPT_CNT = 0;
	}
	else
	{
	/* Report an error if an invalid channel is requested */
		Gpt_ReportError(GPT_E_PARAM_INVALID_CHANNEL);
	}
}

void Gpt_SetCallback(Gpt_ChannelType Channel, Gpt_CallbackType Callback) {
    if (Channel < GPT_MAX_CHANNELS) {
        Gpt_Callbacks[Channel] = Callback;
    } else {
        Gpt_ReportError(GPT_E_PARAM_INVALID_CHANNEL);
    }
}

void GPT_IRQHandler(void) {
	if (GPT_SR & GPT_SR_UIF) {
		/* Clear the interrupt flag*/
		GPT_SR &= ~GPT_SR_UIF;

		/*Call the callback function if set */
		if (Gpt_Callbacks[0] != NULL) {
			Gpt_Callbacks[0]();
		}
	}
}

