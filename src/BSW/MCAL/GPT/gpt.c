/* gpt.c */
#include "Gpt.h"

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
}

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    /* Check if the channel is valid */
    if (Channel < GPT_MAX_CHANNELS)
    {
        /* Set the value to start the timer */
        GPT_CNT = Value;
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
        GPT_CNT = 0;
    }
    else
    {
        /* Report an error if an invalid channel is requested */
        Gpt_ReportError(GPT_E_PARAM_INVALID_CHANNEL);
    }
}

