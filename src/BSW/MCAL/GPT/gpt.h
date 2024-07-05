/**
 * @file gpt.h
 * @brief gpt driver header file
 */
#ifndef GPT_H
#define GPT_H

#include "Std_Types.h"


#define GPT_BASE_ADDRESS 0x40012C00 

/* Define the GPT Control Register 1 */
#define GPT_CR1   (*((volatile uint32_t *)(GPT_BASE_ADDRESS + 0x00)))

/* Define the GPT Auto-Reload Register */
#define GPT_ARR   (*((volatile uint32_t *)(GPT_BASE_ADDRESS + 0x08)))

/* Define the GPT Counter Register */
#define GPT_CNT   (*((volatile uint32_t *)(GPT_BASE_ADDRESS + 0x0C)))

/* Define the GPT Control Register 1 Bit */
#define GPT_CR1_EN (1 << 0)  /* Enable GPT */

/* Define the maximum number of GPT channels */
#define GPT_MAX_CHANNELS 4

typedef unsigned int Gpt_ChannelType;
typedef unsigned int Gpt_ValueType;
typedef unsigned int Std_ReturnType;

/* Define the callback function type for GPT */
typedef void (*Gpt_CallbackType)(void);

/* Define the configuration structure for GPT */
typedef struct {
    Gpt_ValueType Period;          /* Period of the GPT timer */
    Gpt_CallbackType Callback;     /* Callback function for GPT interrupt */
} Gpt_ConfigType;

/* Define the error codes for GPT */
#define GPT_E_PARAM_INVALID_CHANNEL    0x01
#define GPT_E_PARAM_INVALID_VALUE      0x02
#define GPT_E_PARAM_NULL_PTR		   0x03

/* Function prototypes */
void Gpt_Init(const Gpt_ConfigType* ConfigPtr);
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);
void Gpt_StopTimer(Gpt_ChannelType Channel);
void Gpt_SetCallback(Gpt_ChannelType Channel, Gpt_CallbackType Callback);
void Gpt_ReportError(uint8_t ErrorCode);
void GPT_IRQHandler(void);

#endif /* GPT_H */
