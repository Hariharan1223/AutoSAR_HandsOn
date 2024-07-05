/**
 * @file dio.h
 * @brief dio driver header file
 */
#ifndef DIO_H
#define DIO_H

typedef unsigned int Dio_LevelType 
typedef unsigned int Dio_ChannelType
typedef unsigned int Std_ReturnType;

/* Physical state 0V */
#define STD_LOW	0x00  
 /* Physical state 5V or 3.3V */
#define STD_HIGH 0x01

#define GPIO_PORTA_PIN3	3
/* Assuming the base address of GPIO port A */
#define GPIOA_BASE_ADDRESS	0x40020000  
/* Input Data Register */
#define GPIO_IDR (*((volatile uint32_t *)	(GPIOA_BASE_ADDRESS + 0x10))) 
/* Output Data Register */
#define GPIO_ODR (*((volatile uint32_t *)	(GPIOA_BASE_ADDRESS + 0x14)))

/* Error codes */
#define DIO_E_PARAM_INVALID_CHANNEL_ID 0x01
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Function to report errors */
void Dio_ReportError(uint8_t ErrorCode);

#endif /*DIO_H*/